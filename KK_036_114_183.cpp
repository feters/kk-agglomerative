#include <cstdio>
#include <math.h>
#include <stdio.h>

int main()
{
    int i=0, data=30, attribute=20, cluster=4, memberNumber=1, c1=0, c2=0, c3=0, c4=0;
    int merge_1, merge_2, coba=0;
    int status[200], member[200], types[200];
    int initTables[200][200];
    float similar=99, proxMatrix[200][200], centroCluster[200][200], centro=0;
    
    FILE *fdataset;
	
	fdataset = fopen("dataset-om2.txt", "r");
	
	while(fscanf(fdataset, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", 
	&initTables[i][1], &initTables[i][2], &initTables[i][3], &initTables[i][4], &initTables[i][5], 
	&initTables[i][6], &initTables[i][7], &initTables[i][8], &initTables[i][9], &initTables[i][10], 
	&initTables[i][11], &initTables[i][12], &initTables[i][13], &initTables[i][14], &initTables[i][15], 
	&initTables[i][16], &initTables[i][17], &initTables[i][18], &initTables[i][19], &initTables[i][20])!=EOF){
		i++;                                                                                                                        
	}                                                                                                                            


    for(int i=1; i<=data; i++)
    {
        for(int j=1; j<=data; j++)
        {
            for(int k=1; k<=attribute; k++)
            {
                proxMatrix[i][j] += pow(initTables[i][k] - initTables[j][k] , 2);
            }
            proxMatrix[i][j] = sqrt(proxMatrix[i][j]);
        }
    }

    for(int i=1; i<=data; i++)
    {
        for(int j=1; j<=i; j++)
        {
            if(proxMatrix[i][j] > 0 && proxMatrix[i][j] < similar)
            {
                similar = proxMatrix[i][j];
                merge_1 = j;
                merge_2 = i;
            }
        }
    }

    similar = 99;
    member[merge_1] = memberNumber;
    member[merge_2] = memberNumber;
    status[merge_2] = 1;

    for(int z=1; z<data-cluster; z++)
    {
        for(int i=1; i<=data; i++)
        {
            if(proxMatrix[merge_1][i] > 0 && proxMatrix[merge_2][i] > 0 && proxMatrix[merge_1][i] < proxMatrix[merge_2][i])
            {
                proxMatrix[merge_1][i] = proxMatrix[merge_2][i];
                proxMatrix[i][merge_1] = proxMatrix[merge_2][i];
            }
            else
            {
                proxMatrix[merge_1][i] = proxMatrix[merge_1][i];
                proxMatrix[i][merge_1] = proxMatrix[merge_1][i];
            }
        }

        for(int i=1; i<=data; i++)
        {
            if(status[i] == 1) continue;
            else
            {
                for(int j=1; j<=i; j++)
                {
                    if(status[j] == 1) continue;
                    else
                    {
                        if(proxMatrix[i][j] > 0 && proxMatrix[i][j] < similar)
                        {
                            similar = proxMatrix[i][j];
                            if(i < j)
                            {
                                merge_1 = i;
                                merge_2 = j;
                            }
                            else
                            {
                                merge_1 = j;
                                merge_2 = i;
                            }
                        }
                    }
                }
            }
        }

        similar = 99;

//--------untuk mencari nilai paling kecil yang akan ditukar-----------
        if(member[merge_1] > 0)
        {
            if(member[merge_2] == 0)
            {
                member[merge_2] = member[merge_1];
            }
            else
            {
                if(member[merge_1] < member[merge_2])
                {
                    coba = member[merge_2];
                    for(int i=1; i<=data; i++)
                    {
                        if(member[i] == coba)
                            member[i] = member[merge_1];

                    }
                }
                else
                {
                    coba = member[merge_1];
                    for(int i=1; i<=data; i++)
                    {
                        if(member[i] == coba)
                            member[i] = member[merge_2];
                    }
                }
            }
        }
        else if(member[merge_2] > 0)
        {
            member[merge_1] = member[merge_2];
        }
        else
        {
            memberNumber++;
            member[merge_1] = memberNumber;
            member[merge_2] = memberNumber;
        }

        status[merge_2] = 1;

    }

    for(int i=0; i<data; i++)
    {
        if(member[i] == 0)
        {
            member[i] = memberNumber;
            memberNumber++;
        }
    }

    int hitung=0, klaster=1, temp;
    for(int i=1; i<=data; i++)
    {
        for(int j=1; j<=data; j++)
        {
            if(member[j]==i)
            {
                temp=i;
                while((temp - klaster) > 1)
                        temp--;
                member[j] = temp;
                hitung++;
            }
        }
        hitung=0;
        klaster=temp;
    }

    hitung=0;
    for(int i=1; i<=attribute; i++)
    {
        for(int j=1; j<=data; j++)
        {
            for(int k=1; k<=data; k++)
            {
                if(member[k] == j)
                {
                    centro += initTables[k][i];
                    centroCluster[k][i] = centro;
                    hitung++;
                }
            }

            for(int k=1; k<=data; k++)
            {
                if(member[k] == j)
                {
                    centroCluster[k][i] = centro/hitung;
                }
            }
            centro=0;
            hitung=0;
        }

    }
    
    for(int i=1; i<=cluster; i++)
    {
        for(int j=1; j<=data; j++)
        {
            if(member[j]==i){
            	if(c1==0 && i==1) c1=j;
            	else if(c2==0 && i==2) c2=j;
            	else if(c3==0 && i==3) c3=j;
            	else c4=j;
            }
        }
    }
	
	printf("centroid 1: %d\n",c1);
	printf("centroid 2: %d\n",c2);
	printf("centroid 3: %d\n",c3);
	printf("centroid 4: %d\n",c4);
	printf("\n");
	
	int om1, om2, om3, om4, cek1=0, cek2=0, cek3=0, cek4=0;
	
	do{
		om1=c1;
		om2=c2;
		om3=c3;
		om4=c4;
		
		for(int i=1; i<=data; i++)
    {
        for(int j=1; j<=data; j++)
        {
            for(int k=1; k<=attribute; k++)
            {
                cek1 += pow(initTables[i][k] - initTables[c1][k] , 2);
                cek2 += pow(initTables[i][k] - initTables[c2][k] , 2);
                cek3 += pow(initTables[i][k] - initTables[c3][k] , 2);
                cek4 += pow(initTables[i][k] - initTables[c4][k] , 2);
            }
            cek1 = sqrt(cek1);
            cek2 = sqrt(cek2);
            cek3 = sqrt(cek3);
            cek4 = sqrt(cek4);
            
            if(cek1<cek2 && cek1<cek3 && cek1<cek4) c1=sqrt(pow(i-10,2));
            if(cek2<cek1 && cek2<cek3 && cek2<cek4) c2=sqrt(pow(i-10,2));
            if(cek3<cek1 && cek3<cek2 && cek3<cek4) c3=sqrt(pow(i-10,2));
            if(cek4<cek1 && cek4<cek3 && cek4<cek2) c4=sqrt(pow(i-10,2));
        }
    }			
		
	}while(c1!=om1 && c2!=om2 && c3!=om3 && c4!=om4);
	
	
    
    printf("Minggu 1: %d\n", c1);   
    printf("Minggu 2: %d\n", c2);    
    printf("Minggu 3: %d\n", c3);    
    printf("Minggu 4: %d\n", c4);		

    return 0;
}
