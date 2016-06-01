#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define PI        3.14
#define length    30		//周期为30，幅值也是30,但是幅值分正负幅值，所以后面的很多地方有length*2
#define delayTime 100000	//100ms刷新一次
#define triAngle  360.0		//圆一周的角度

int main(int argc, char* argv[]){

	int    i            = 0;	//主要用于循环计算
	int    index        = 0;	//用于保存sin曲线上的点的相对于中心轴的偏移
	int    lineNumber   = -1;	//用于保存行号
	double circleAngle  = 0;	//弧度制角度
	/**
	 * 角度制角度，通过传入的参数获取起始角度,
	 * triAngle/length是固定的就是一行所占的角度，
	 * 乘以(atoi(argv[1]))表示起始偏移多少各triAngle/length。
	 */
	double currentAngle =  triAngle/length*(atoi(argv[1])); 

	/**
	 * 这里主要是完成那一行重复的0-9,
	 * length*2是因为sin曲线的最高点和最低点是2倍的幅值，具体可以参见图第3行
	 */
	printf("\n\t");
	for (i = 0; i < length*2; i++) printf("%d", i%10);
	printf("\n");

	while(1){
		/**
		 * 判断是不是最后一行，lineNumber+1 是因为起始行是从0开始
		 */
		if((lineNumber+1) == length){
			//打印每行前面的数字序号
			printf("00%d\t", lineNumber+1);
			for (i = 0; i < length*2; i++)
				//判断是否到达中间位置，因为中间位置要放V的箭头，参见图第33行
				i == length ? printf("V") : printf(" ");	
			break;
		}
		
		lineNumber++;									//行号加1
		currentAngle += triAngle/length;				//在获取了初始值的基础上再加上triAngle/length
		circleAngle = currentAngle/(triAngle/2)*PI;		//由角度制换算成弧度制，主要是因为sin函数需要弧度制
		/**
		 *	算出当前次sin值，并乘以幅值，获取横向位置相对于中心轴的偏移index
		 *	index 可能是正值，也可能是负值，因为中心轴在中间
		 */
		index = sin(circleAngle)*length;				

		/**
		 * 行号可能是一个数字，也可能是2个数字，需要分别处理
		 * 当然你可以直接使用printf("%03d", lineNumber);效果是相同的
		 */
		if(lineNumber / 10 == 0) printf("000%d", lineNumber);
		else if(lineNumber / 100 == 0) printf("00%d", lineNumber);

		/**
		 * 用一个制表符，给出行号与图形的空间距离
		 */
		printf("\t");

		/**
		 * 第一行，参见图第3行
		 */
		if(lineNumber == 0){
			for (i = 0; i < length*2; i++){
				i == length ? printf("*") : printf("-");
			}
			printf("-> Y\n");
		}else {
			for (i = 0; i < length*2; i++){
				//判断是否到了sin曲线上的点，是的话输出*
				if(i == (index+length)){
					printf("*");
				//判断是否到了中间线，是的话输出|
				}else if(i == length){
					printf("|");
				}else{
					/**
					 * 这里主要是要处理一行里面除了画'*'、'|'、之外的'-'、' '
					 * 其中的length到length+index正好就是需要需要打'-'的地方
					 * 其他的地方输出' '
					 */
					(((i > length) && (i < length+index)) || 
							((i < length) && (i > length+index))) ? printf("-") : printf(" ");
				}
				//行尾，输出换行符
				if(i == (length*2-1)) printf("\n");
			}
		}
	}
	printf("\n\n\n");
	usleep(delayTime);

	return 0;
}
