/*
 * 用户输入M,N值，从1至N开始顺序循环数数，每数到M输出该数值，直至全部输出
 */
#include <stdio.h>
#include <stdlib.h> 

struct number
{
	int num;
    struct number * next;
};

int main()
{
	int m, n;
	int i = 0,j = 0,t = 0;
	struct number * p, * head=NULL, * tail, *q;

	printf("please input M and N:\n");
	scanf("%d %d", &m, &n);          //输入M、N值。
	for(i=1; i<=n; i++)               //建立循环链表。
	{
		p=(struct number *)malloc(sizeof(struct number));
		p->num=i;
		if(head==NULL)
		{
			head=p;
			tail=p;//注意开始tail也要赋值
		}
		else
			tail->next=p;
		tail=p;
	}
	tail->next=head;
	p = tail;  //从head开始，记录开始的前一个指针
	while(n)   //剩下的数的个数为n                                         
	{       
		t = m%n; //防止多数太多圈造成时间浪费                               
		for(j=1; j<t;j++ )       //数到要删的那个数的前一个                   
			p=p->next;  
		q = p->next;  //要删的数的指针                   
		printf("%d ", q->num);     //输出要删的数          
		p->next = q->next;   //要删的数从链表中去掉
		free(q);   
		n--;        
	} 
	printf("\n");
	return 0;
}

