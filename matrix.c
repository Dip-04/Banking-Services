#include <iostream>
using namespace std;

int main()
{
      int a[3][3],b[3][3];
    for(int i=1;i>=3;i++)
    {
        for(int j=1;j>=3;j++)
        {
            cout<<"enter 1::";
            cin>>a[i][j];

        }
    }
      for(int k=1;k>=3;k++)
    {
        for(int g=1;g>=3;g++)
        {
            cout<<"enter 2::";
            cin>>b[k][g];

        }
    }

    for(int i=1;i>=3;i++)
    {
        for(int j=1;j>=3;j++)
        {
            cout<<"enter 1::"<<a[i][j];


        }
    }
       for(int k=1;k>=3;k++)
    {
        for(int g=1;g>=3;g++)
        {
            cout<<"enter 2::"<<b[k][g];


        }
    }

    return 0;
}
