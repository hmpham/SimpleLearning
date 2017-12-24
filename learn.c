#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check=0;

void check_dia(long double** a,int l,int col){
   if(a[l][l]==1){
      check=1;
      return;
   }
   else{
      long double denominator=a[l][l];
      int i1;
      for(i1=0;i1<(col*2);i1++){
         //printf("%d",col);
         a[l][i1] = a[l][i1]/denominator;
         //printf("%Lf\n",a[col][i1]);
      }
      check=1;
      return;
   }
}

void check_zero(long double** a,int r,int l,int col){
   if(r==l){
      return;
   }
   if(a[r][l]==0){
      return;
   }
   else{
       int i2;
       long double factor=(-1)*a[r][l];
       //printf("%f\n",factor);
       long double b[2*col];
       for(i2=0;i2<(col*2);i2++){
         b[i2] = factor*a[l][i2];
         //printf("%f\n",b[i2]);
       }
       
       int i3;
       for(i3=0;i3<(col*2);i3++){
         //printf("(%f) + (%f)\n",a[row][i3], b[i3]);
         a[r][i3] = a[r][i3] + b[i3];
         //printf("%f\n",a[row][i3]);
       }
    return;
   }
}

long double** multiply(long double** x, long double** t, int row, int col){
  long double** m;
  m=malloc(sizeof(long double*)*col);
  int i;
  for(i=0;i<col;i++){
     m[i]=malloc(sizeof(long double)*col);
  }
  
  for(i=0;i<col;i++){
     int j;
     for(j=0;j<col;j++){
        int k;
        for(k=0;k<row;k++){
           m[i][j]+=t[i][k]*x[k][j];
           //printf("%f ",m[i][j]);
        }
     }
   }
 return m;
}

long double** multiply1(long double** x, long double** t, int row, int col){
  long double** m;
  m=malloc(sizeof(long double*)*col);
  int i;
  for(i=0;i<col;i++){
     m[i]=malloc(sizeof(long double)*row);
  }
  
  for(i=0;i<col;i++){
     int j;
     for(j=0;j<row;j++){
        int k;
        for(k=0;k<col;k++){
           m[i][j]+=x[i][k]*t[k][j];
           //printf("%f ",m[i][j]);
        }
     }
   }
 return m;
}

long double* multiply2(long double** m2,long double y[],int row,int col){

   //long double m3[col];
   long double* m3;
   m3=malloc(sizeof(long double)*col);

int i;
for(i=0;i<col;i++){
 m3[i]=0;
}

//for(i=0;i<col;i++){
//printf("%Lf ",m3[i]);
//}

   for(i=0;i<col;i++){
      int j;
      for(j=0;j<row;j++){
        m3[i] += m2[i][j]*y[j];
      }
   }

 return m3;
}

long double* multiply3(long double** test,long double* w,int row1,int col){

   //long double m3[col];
   long double* f;
   f=malloc(sizeof(long double)*row1);

int i;
for(i=0;i<row1;i++){
 f[i]=0;
}

//for(i=0;i<col;i++){
//printf("%Lf ",m3[i]);
//}

   for(i=0;i<row1;i++){
      int j;
      for(j=0;j<col;j++){
        f[i] += test[i][j]*w[j];
      }
   }

 return f;
}

long double** get_transpose(long double** x,int row, int col){

  long double** t;
  t=malloc(sizeof(long double*)*col);
  int i;
  for(i=0;i<col;i++){
     t[i]=malloc(sizeof(long double)*row);
  }

  for(i=0;i<row;i++){
     int j;
     for(j=0;j<col;j++){
        t[j][i]=x[i][j];
     }
  }
 return t;
}



int main(int argc, char **argv){

FILE *fp;
fp=fopen(argv[1],"r");

  if(fp==NULL){
    printf("error\n");
    return 0;
  }

  char *str=(char*)malloc(100);
  fgets(str,100,fp);
  int col=atoi(str);
  col+=1;
  fgets(str,100,fp);
  int row=atoi(str);

//create y array
  long double y[row];

// create tmp array to store input
 long double tmp[row][col];


//create 2D array size [row][col]
  long double** x;
  x=malloc(sizeof(long double*)*row);
  int i;
  for(i=0;i<row;i++){
     x[i]=malloc(sizeof(long double)*col);
  }
//put 1 into first column of array x
  for(i=0;i<row;i++){
     int j;
     for(j=0;j<col;j++){
        if(j==0)
        x[i][0]=1;
     }
  }

//load array tmp
int ir=0;
  while(ir<row){
    int ic=0;
    fgets(str,1000,fp);
    char *s=(char*)malloc(1000);
    s=strtok(str,",");
    while(s!=NULL){
      tmp[ir][ic]=atof(s);
      ic++;
      s=strtok(NULL,",");
    }
    ir++;
}
//load tmp -> x array
  int ii;
  for(i=0,ii=0;i<row;i++,ii++){
     int j,jj;
     for(j=1,jj=0;j<col;j++,jj++){
        x[i][j]=tmp[ii][jj];
     }
  }
//load tmp -> y array
  for(i=0;i<row;i++){
    int j;
    for(j=0;j<col;j++){
       if(j==(col-1)){
          y[i]=tmp[i][j];
       }
    }
  }

long double** t = get_transpose(x,row,col);

long double** m1 = multiply(x,t,row,col);


//create array gauss
long double** gauss;
  gauss=malloc(sizeof(long double*)*(col));
  for(i=0;i<col;i++){
     gauss[i]=malloc(sizeof(long double)*(col*2));
  }

//load array m1 to gauss
for(i=0;i<col;i++){
     int j;
     for(j=0;j<col;j++){
        gauss[i][j] = m1[i][j];
     }
  }

//load 1 to diagonal
int j;
for(i=0,j=col;i<col;i++,j++){
  gauss[i][j]=1;
}

for(i=0;i<col;i++){
     int j;
     for(j=0;j<col;j++){
        gauss[i][j] = m1[i][j];
     }
  }

for(i=0;i<col;i++){
  check=0;
     for(j=0;j<col;j++){
        //check for diagonal
         if(check==0){
              check_dia(gauss,i,col);
         }
         check_zero(gauss,j,i,col);
     }
  }

//create array inverse
long double** in;
  in=malloc(sizeof(long double*)*(col));
  for(i=0;i<col;i++){
     in[i]=malloc(sizeof(long double)*(col));
  }

//load gauss -> inverse

for(i=0;i<col;i++){
     int j,jj;
     for(jj=0,j=col;j<(col*2);j++,jj++){
        in[i][jj]=gauss[i][j];
     }
  }

long double** m2 = multiply1(in,t,row,col);

long double* w = multiply2(m2,y,row,col);

fp=fopen(argv[2],"r");

  if(fp==NULL){
    printf("error\n");
    return 0;
  }

  fgets(str,100,fp);
  int row1=atoi(str);

  long double** test;
  test=malloc(sizeof(long double*)*row1);
  for(i=0;i<row1;i++){
     test[i]=malloc(sizeof(long double)*col);
  }

  ir=0;
  while(ir<row1){
    int ic=1;
    fgets(str,1000,fp);
    char *s=(char*)malloc(1000);
    s=strtok(str,",");
    while(s!=NULL){
      test[ir][ic]=atof(s);
      ic++;
      s=strtok(NULL,",");
    }
    ir++;
}

i=0;
while(i<row1){
   test[i][0]=1;
   i++;
}

long double* f = multiply3(test,w,row1,col);

for(i=0;i<row1;i++){
  printf("%0.0Lf\n",f[i]);
}

return 0;
}


