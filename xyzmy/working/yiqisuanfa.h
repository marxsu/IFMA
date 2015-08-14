#ifndef YIQISUANFA_H
#define YIQISUANFA_H
void checkTest(double data[],int i,double result[])
{
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
    int c = 0;
    char output[10];
    data[0] = -1;//避免数据线一开始处于较高的位置,影响峰值的判断.

    for(int j=0;j<i-testwindowsize+1;j++)
    {
       if(c==4) break;
       double sum = 0.0;
       for(int k=j;k<testwindowsize+j;k++)
       {
            sum += daoshudata[k];
       }
       avg=sum/testwindowsize;
       if(avg>=0.4 && j>=200 && j<=1100 && !flag1)
       {
          flag1 = true;
          feng[c] = j;
          c++;
       }
       else if(flag1 & !flag2)
       {
         if(avg<-0.5)
         {
             flag2 = true;
         }
         if(data[j]>data[feng_max[c/2]])
         {
             feng_max[c/2]=j;

         }
          if(j==500 || j==900)
         {
             flag2 = true;//因为下降过缓,导致没有正确判断时,当到达第500和第900点时,开始判断终止点
         }
       }
       else if(flag1 && flag2 && (avg>=-0.5|| j==1100) )
       {
          flag1 = false;
          flag2 = false;
          feng[c]=j;
          c++;
       }
    }
    double bendi=0;
    double sum_bendi=0;
    for(int j=(feng_max[0]+feng_max[1])/2-20;j<(feng_max[0]+feng_max[1])/2+21;j++)
    {
         sum_bendi+=data[j];

    }
    bendi=sum_bendi/(41.0);

    for(int j=0;j<c/2;j++)
    {
      if(j==0)
      {
        int mianji=0;
        if(feng[j+1]-feng[j]>=50)
        {
            for(int x=feng_max[j]-20;x<feng_max[j]+21;x++)
            {

            // mianji+=(data[x]);
               mianji+=(data[x]-bendi);
            }
            result[0]=mianji;
        }
        else
        {
            result[0]=0;
        }
      }
      else if(j==1)
      {
        double mianji=0;
        if(feng[j+2]-feng[j+1]>=50)
        {
            for(int x=feng_max[j]-20;x<feng_max[j]+21;x++)
            {

            // mianji+=(data[x]);
               mianji+=(data[x]-bendi);
            }
            result[1]=mianji;
        }
        else
        {
            result[1]=0;
        }
      }
    }
    delete []pinghuadata;
    delete []daoshudata;
}
#endif // YIQISUANFA_H
