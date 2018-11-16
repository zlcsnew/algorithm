#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;
struct heap{
    int posi;
    struct heap * next;
};
int Assign(vector<int> monkey_vector,vector<int> banana_vector);
vector<int> monkey_vector;
vector<int> banana_vector;
struct heap * head=NULL,*tail=NULL,*tmp;
void initVector(vector<int> * vector_head){
     int tmp_scanf,goon=1,first_time=1;
     while (goon){
          scanf("%d",&tmp_scanf);
          (*vector_head).push_back(tmp_scanf);
          if (getchar()=='\n')
               goon=0;
     }
}
void debug(vector<int> * vector_head){
     int i=0;
     printf("=======start=========\n");
     printf("%lu \n",(*vector_head).capacity());
     for (;i<(*vector_head).size();i++)
          printf("%d ",(*vector_head)[i]);
     printf("\n=======end=======\n");
}

int main(){ 
    initVector(&monkey_vector);
    initVector(&banana_vector);
    sort(monkey_vector.begin(),monkey_vector.end());
    sort(banana_vector.begin(),banana_vector.end()); 
    //debug(&monkey_vector);
    //debug(&banana_vector);
    int max=Assign(monkey_vector,banana_vector);
    printf("%d",max);
}

int Assign(vector<int> monkey_vector,vector<int> banana_vector){
     int first_heap_time=0,max=0;
     int i=0,now_banana=0;
     unsigned int monkey_size=monkey_vector.size();
     while(i<monkey_size&&(now_banana<monkey_size||head!=NULL)){
            if (head!=NULL){
                 if (max<(monkey_vector[i]-head->posi))
                        max=monkey_vector[i]-head->posi;
                 i=i+1;
                 tmp=head;
                 head=head->next;
                 free(tmp);
            }else if (banana_vector[now_banana]>=monkey_vector[i]){
                 if (max<banana_vector[now_banana]-monkey_vector[i])
                          max=banana_vector[now_banana]-monkey_vector[i];
                 i=i+1;
                 now_banana++;
            }else{
                 tmp=(struct heap *)malloc(sizeof(struct heap));
                 if (head==NULL){
                     head=tmp;
                     tail=head;
                     tail->next=NULL;
                     tail->posi=banana_vector[now_banana];
                 }else{
                     tmp->posi=banana_vector[now_banana];
                     tmp->next=NULL;
                     tail->next=tmp;
                     tail=tail->next;
                 }
                 now_banana++;
            }
     }
     return max;
}
