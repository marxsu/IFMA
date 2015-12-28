#ifndef YIQISUANFA_H
#define YIQISUANFA_H

typedef struct {
    int start;  //波峰起始点
    int end;    //波峰终止点
    int jiange; //波峰宽度
    int max;    //波峰最高点位置
    int height;  //波峰高度  新增
} Peak;

int PeakNum = 10;
Peak *peak = new Peak[PeakNum];    //假设有10个波峰

//按波峰高度进行降序排序
//快速排序
void quick_sort_by_height(Peak *peak, int l, int r, double *data)
{
    if(l < r)
    {
        int i=l, j=r;
        Peak tmp = peak[l];
        while(i < j)
        {
            while(i < j && peak[j].height <= tmp.height)   //从右向左找到第一个大于tmp的数
                j--;
            if(i < j)
                peak[i++] = peak[j];
            while(i < j && peak[i].height > tmp.height)   //从左往右找到第一个小于等于tmp的数
                i++;
            if(i < j)
                peak[j--] = peak[i];
        }
        peak[i] = tmp;
        quick_sort_by_height(peak, l, i-1, data);
        quick_sort_by_height(peak, i+1, r, data);
    }
}

//按波峰峰值进行降序排序
//快速排序
void quick_sort_by_max(Peak *peak, int l, int r, double *data)
{
    if(l < r)
    {
        int i=l, j=r;
        Peak tmp = peak[l];
        while(i < j)
        {
            while(i < j && data[peak[j].max] <= data[tmp.max])   //从右向左找到第一个大于tmp的数
                j--;
            if(i < j)
                peak[i++] = peak[j];
            while(i < j && data[peak[i].max] > data[tmp.max])   //从左往右找到第一个小于等于tmp的数
                i++;
            if(i < j)
                peak[j--] = peak[i];
        }
        peak[i] = tmp;
        quick_sort_by_max(peak, l, i-1, data);
        quick_sort_by_max(peak, i+1, r, data);
    }
}


void checkTest(double data[],int i,double result[], double originData[])
{
    int DynamicThreshold = 0; //动态阈值

    //结构体初始化
    for(int i=0; i<PeakNum; i++)
    {
        peak[i].start = 0;
        peak[i].end = 0;
        peak[i].jiange = 0;
        peak[i].max = 0;
        peak[i].height = 0;
    }

    double *pinghuadata = new double[i];
    double *daoshudata = new double[i];
    for(int j=0;j<10/2;j++)
    {
      pinghuadata[j]=data[j];

    }
    for(int j=10/2;j<i-10/2;j++)
    {
       double avg = 0,sum = 0;
       for(int k=j-10/2;k<10+j-10/2+1;k++)
       {
           sum += data[k];
       }
       avg = sum/(11.0);
      pinghuadata[j]=avg;

    }
    for(int j=i-10/2;j<i;j++)
    {
      pinghuadata[j]=data[j];
    }

    for(int j=0;j<i;j++)
    {
       if(j==0)
       {
          daoshudata[j]=pinghuadata[j+1]-pinghuadata[j];
       }
       else if(j==i-1)
       {
          daoshudata[j]=pinghuadata[j]-pinghuadata[j-1];
       }
       else
       {
          daoshudata[j]=(pinghuadata[j+1]-pinghuadata[j-1])/2.0;

       }
    }

    int testwindowsize=10;

    double avg=0.0;
    bool flag1 = false;
    bool flag2 = false;
    int feng_max[2] = {0};
    int feng[4]={0};
    int count = 0;
    data[0] = -1;//避免数据线一开始处于较高的位置,影响峰值的判断.

    for(int j=0;j<i-testwindowsize+1;j++)
    {
       double sum = 0.0;
       for(int k=j;k<testwindowsize+j;k++)
       {
            sum += daoshudata[k];
       }
       avg=sum/testwindowsize;
       if(avg>=0.4  &&  !flag1)
       {
          flag1 = true;   //找到波峰起始点
          peak[count].start = j;  //记录波峰起始点位置
       }
       else if(flag1 & !flag2)
       {

         if(avg<-0.5)
         {
             flag2 = true;
         }
         if(data[j]>data[peak[count].max])  //找平滑后数据的最高点
          {
              peak[count].max = j;
          }
//          if(j==500 || j==900)
//         {
//             flag2 = true;//因为下降过缓,导致没有正确判断时,当到达第500和第900点时,开始判断终止点
//         }
       }
       else if(flag1 && flag2)
       {
           if(data[j]>data[peak[count].max])  //找平滑后数据的最高点
            {
                peak[count].max = j;
            }

           if ((avg>=-0.5|| j==1100))  //找到波峰终止点
             {
                 flag1 = false;
                 flag2 = false;
                 peak[count].end = j;  //记录波峰终止点位置
                 peak[count].jiange = peak[count].end - peak[count].start; //波峰宽度
                  peak[count].height = data[peak[count].max] - data[peak[count].end]; //波峰高度
                 count++;  //下一个波峰
             }
       }
    }


    //按波峰峰值进行降序排序
    //快速排序
    //quick_sort_by_max(peak, 0, PeakNum-1, data);

    //按波峰高度进行降序排序
    //快速排序
    quick_sort_by_height(peak, 0, PeakNum-1, data);


    //波峰判断
    if(peak[0].max > 0 && peak[0].max < 600)  //第一个波峰最高点位置处于0-600之间
    {
        //为第一个波峰
        feng[0] = peak[0].start;
        feng[1] = peak[0].end;
        feng_max[0] = peak[0].max;
    }
    else if(peak[0].max > 600 && peak[0].max < 1100) //第二个波峰最高点位置处于600-1100之间
    {
        //为第二个波峰
        feng[2] = peak[0].start;
        feng[3] = peak[0].end;
        feng_max[1] = peak[0].max;
    }

    if(peak[1].max > 0 && peak[1].max < 600)  //第一个波峰最高点位置处于0-600之间
    {
        //为第一个波峰
        feng[0] = peak[1].start;
        feng[1] = peak[1].end;
        feng_max[0] = peak[1].max;
    }
    else if(peak[1].max > 600 && peak[1].max < 1100) //第二个波峰最高点位置处于600-1100之间
    {
        //为第二个波峰
        feng[2] = peak[1].start;
        feng[3] = peak[1].end;
        feng_max[1] = peak[1].max;
    }

    //设定动态阈值，如果基线是平的，阈值低一点，如果基线有波动，阈值高一点
    if (peak[2].height > 0)
    {
        for(int k=2; k<PeakNum; k++)
        {
            if (peak[k].max>feng[1] && peak[k].max<feng[2])  //T峰跟C峰之间存在波动
            {
                //存在波动
                DynamicThreshold = peak[k].height;
                break;
            }
            else
            {
                //不存在波动
                DynamicThreshold = 0;
            }
        }
    }
    else
    {
        //不存在波动
        DynamicThreshold = 0;
    }


    //结果
    if((feng[1]!=0) && ((data[feng_max[0]]-data[feng[1]]) > DynamicThreshold))
    {
        result[0] = data[feng_max[0]];  //直接取峰值，不算面积
    }
    else
    {
        result[0] = 0;
    }

    if((feng[3]!=0) && ((data[feng_max[1]]-data[feng[3]]) > DynamicThreshold))
    {
        result[1] = data[feng_max[1]];  //直接取峰值，不算面积
    }
    else
    {
        result[1] = 0;
    }

    delete [] pinghuadata;
    delete [] daoshudata;
    delete [] peak;
}
#endif // YIQISUANFA_H
