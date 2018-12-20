#include<stdlib.h>
#include<stdio.h>
double processMinLPWithOutInit(double **array,int lineNum,int rowNum,int baseNumber,int **baseVector,int *flag);
//double processMinLP(double *array,int lineNum,int rowNum,int baseNumber,int *flag);
double getMinResult(double *array,int rowNum);
void debugInfo(double **array,int lineNum,int rowNum){
    int i=0,j=0;
    printf("\n******debug info:lineNum,rowNum:%d,%d******\n",lineNum,rowNum);
    for(;i<lineNum;i++){
            for (j=0;j<rowNum;j++){
                printf("%lf ",(*array)[rowNum*i+j]);
            }
            printf("\n");
    }
}
double getMinResult(double *array,int rowNum){
    return array[rowNum-1];
}

/*
    arrayTrain:
    min     x 0
    s.t. −x 1 − x 2 −x 0 +x 3 = −1
        x 1 + x 2 −x 0 +x 4 = 2
        x 1 , x 2 ,x 0 ,x 3 ,x 4 ≥ 0
*/

int InitializeSimplex(double **arrayTrain,double **arrayTest,int lineNum,int rowNumTrain,int rowNumTest,int **baseVector){
    int min_Bindex,minB=0,B_base=2*rowNumTrain-1,i=0,j,baseLineIndex,baseLineIndexTest;
    int flag;
    double result;
    int x0Index=rowNumTrain-lineNum-1;
    for(i=1;i<lineNum;i++){
        if ((*arrayTrain)[B_base]<minB){
            min_Bindex=i;
            minB=(*arrayTrain)[B_base];
        }
	    B_base+=rowNumTrain;
    }
    if (minB>=0)
        return 1;//成功
// void Pivot(double **array,int lenNum,int lenPerLine,int x,int y,int **baseVector)
    //printf("lineNum,rowNumTrain,x,y:%d,%d,%d,%d\n",lineNum,rowNumTrain,min_Bindex,rowNumTrain-1-lineNum);
    Pivot(arrayTrain,lineNum,rowNumTrain,min_Bindex,rowNumTrain-1-lineNum,baseVector);
    debugInfo(arrayTrain,lineNum,rowNumTrain);
    printf("after pivot index:%d,%d,%d\n",(*baseVector)[0],(*baseVector)[1],(*baseVector)[2]);
//double processMinLPWithOutInit(double **array,int lineNum,int rowNum,int baseNumber,int **baseNumber,int *flag)
    result=processMinLPWithOutInit(arrayTrain,lineNum,rowNumTrain,lineNum-1,baseVector,&flag);
    printf("after MinLP index:%d,%d,%d\n",(*baseVector)[0],(*baseVector)[1],(*baseVector)[2]);
    //debugInfo(arrayTrain,lineNum,rowNumTrain);             
    //printf("x0Index:%d",x0Index);
    if (flag==1)
        if (result==0){
            printf("has inital\n");
            for (i=1;i<lineNum;i++){
                baseLineIndex=i*rowNumTrain;
                baseLineIndexTest=i*rowNumTest;
                printf("lindex,test:%d,%d,%d\n",baseLineIndex, baseLineIndexTest,x0Index);
                for (j=0;j<rowNumTrain;j++){
                    if(j<x0Index){
                        (*arrayTest)[baseLineIndexTest+j]=(*arrayTrain)[baseLineIndex+j];
                    }else if (j>x0Index){     
                        (*arrayTest)[baseLineIndexTest+j-1]=(*arrayTrain)[baseLineIndex+j];
                    }
                }
            }
            printf("has changed\n");
            //(*baseVector)[1]=4;
            debugInfo(arrayTest,lineNum,rowNumTest);             
            //printf("before changed index:%d,%d\n",(*baseVector)[0],(*baseVector)[1]);
            int baseRow;
            for (i=0;i<lineNum-1;i++){//基坐标
                if ((*baseVector)[i]>x0Index)
                      (*baseVector)[i]--;
                baseRow=(*baseVector)[i];
                if ((*arrayTest)[baseRow]==0)
                    continue;
                for (j=1;j<rowNumTest;j++)
                    if ((*arrayTest)[j*rowNumTest+baseRow]==1)
                        break;
                int m=0;
                double basefactor=(*arrayTest)[baseRow];
                int opq=j*rowNumTest;
                printf("basefactor:%lf\n",basefactor);
                for (;m<rowNumTest;m++)
                    (*arrayTest)[m]-=basefactor*(*arrayTest)[opq+m];
            }
            printf("after changed index:%d,%d\n",(*baseVector)[0],(*baseVector)[1]);
            printf("init all ok\n");
            //debugInfo(arrayTest,lineNum,rowNumTest);
            printf("\n");
            return 1;
        }
    return 0;
}
/*
    @input:array，需要行变换的矩阵;lineNum，矩阵的行数；i,j,确定baseNumber的坐标；lenPerLen，每一行参数的个数
    @output:进行行变换后的矩阵;复杂度:O(nm)
    stat:已完成
*/
void  lineChange(double ** array,int lineNum,int i,int j,int lenPerLen){
    int now_line=0,baseNumber_index=i*lenPerLen+j;
    double baseNumber=(*array)[baseNumber_index];
    for (;now_line<lineNum;now_line++){
        int needChange_index=now_line*lenPerLen+j;
        if ((*array)[needChange_index]==0||now_line==i)
            continue;
        int nowLenStart=now_line*lenPerLen,nowLineEnd;
        nowLineEnd=nowLenStart+lenPerLen;
        int nowBase_index=i*lenPerLen;
        double basefactor=(*array)[needChange_index]/baseNumber;
        for (;nowLenStart<nowLineEnd;nowLenStart++,nowBase_index++)
            (*array)[nowLenStart]-=(*array)[nowBase_index]*basefactor;
    }
}

/*
    @input:array,lenPerLine:确定检查向量;
    @output:baseVector:基向量的列标,复杂度o(n)
*/
void getBaseVector(double *array,int lenPerLine,int **baseVector,int rowNew,int rowOld,int index4base){
    (*baseVector)[index4base]=rowNew;  
}

/*
    input:array,矩阵;lenPerline,检查向量的数量;lineNum,行数；
    output:x,y,minT  下一个参考点的横纵坐标，及最小值
    复杂度:o(m+n)
*/
void getMaxIndex(double *array,int lenPerLine,int lineNum,int *x,int *y,double *minT,int *flag){
    int i=0,j,tmpIndex,indexDiff=0;
    double tmpMin=0.0,nowT=1000000000;
    *minT=nowT;
    for (;i<lenPerLine-1;i++)//lenPerline-1是b对应的检查子
        if (array[i]<tmpMin){
            (*y)=i;
            tmpMin=array[i];
        }
            
    if (tmpMin==0){
        *flag=1;
        return;
    }
    indexDiff=lenPerLine-1-(*y);
    for (j=1;j<lineNum;j++){
        tmpIndex=j*lenPerLine+(*y);
        if (array[tmpIndex]>0){
            nowT=array[(j+1)*lenPerLine-1]/array[tmpIndex];
            if (nowT<*(minT)){
                *minT=nowT;
                *x=j;
            }
        }
    }
    if (nowT==1000000000)
        *flag=2;
}

/*
    input:array,lenNum,lenPerLine,同上;x,y,参考点坐标
    output:此时的基向量,经过行变换的数组
    时间复杂度:o(mn)
*/
void Pivot(double **array,int lenNum,int lenPerLine,int x,int y,int **baseVector){
    //第x行归一化
    int i=0,nowIndex,nowEndIndex,baseIndex;
    nowIndex=x*lenPerLine;
    nowEndIndex=(x+1)*lenPerLine;
    baseIndex=nowIndex+y;
    int oldIndex=-1;
    double basefactor=(*array)[baseIndex];
    for (;nowIndex<nowEndIndex;nowIndex++){
        (*array)[nowIndex]/=basefactor;
    }
    lineChange(array,lenNum,x,y,lenPerLine);
    for(i=0;i<lenNum;i++){
        int tmpIndex=(*baseVector)[i];
        if ((*array)[tmpIndex]!=0){
            oldIndex=(*baseVector)[i];
            break;
        }
    }
    getBaseVector(*array,lenPerLine,baseVector,y,oldIndex,i);
}

double processMinLPWithOutInit(double **array,int lineNum,int rowNum,int baseNumber,int **baseVector,int *flag){
    //int *baseVector=(int *)calloc(baseNumber,sizeof(int));
    int x,y;
    double minT;
    double result;
    int flag1=0;
    *flag=1;
    int i;
    //debugInfo(array,lineNum,rowNum);
    while(1){
        getMaxIndex(*array,rowNum,lineNum,&x,&y,&minT,&flag1);
        if (flag1==1){
            result=getMinResult(*array,rowNum);
	        return 0-result;
	    }
        else if (flag1==2){
            *flag=0;
            return 0;
        }
        Pivot(array,lineNum,rowNum,x,y,baseVector);
        debugInfo(array,lineNum,rowNum);
    }
}
