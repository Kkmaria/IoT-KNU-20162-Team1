#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct word{//�ܾ� ��� ���� ����
	char wname[20];
	int index;
	struct word *link;
}word;

char name[20];//�ܾ� �о ��忡 �����ϱ� ���� �ӽ� �����.

void main(){
	int a=0;
	int b=-1;
	int number=0;//�� ��� �ε����� �����ϱ� ���� ����
	char space=' ';//�˻��� �������� �ܾ�� �ܾ� ���̸� �������� ����.
	char buffer[256];//���� �о�� ���� �� ��Ʈ��.
	word *W,*WW;	//����Ʈ�� ù ��带 �����ϱ� ���� ������
	word *W1;
	word *W2;//�������� �Ҵ��� �޸� ������
	FILE *fp=NULL;
	char fname[128];//�����̸��� �����ϱ� ���� ���ڿ�
	char wordname[20];//�˻��� �ܾ�

	printf("�����̸�: ");
	scanf("%s",fname);
	if((fp=fopen(fname,"r"))==NULL)//���Ͽ���.
	{
		fprintf(stderr,"���� %s�� �� �� �����ϴ�.",fname);
		exit(1);
	}
	W1=(word*)malloc(sizeof(word));
	W1->link=NULL;
	

	while(fgets(buffer,256,fp)){//�ܾ ���� �޾ƿ��� �ݺ���(string ������ �о��)
		for(int n=0;n<256;n++)
		{
			if((buffer[n]==space)||(buffer[n]==NULL)){//������ �����ų� string�� ���� ������
				number++;//�ε��� �ѹ� ����
				for(int m=1;m<=(n-a);m++)name[m-1]=buffer[b+m];//���� ���� ���� �� ���� ���� ���� ���� �� ������ buffer[]�� name[]�� ����
				b=n;
				a=b+1;
				W2=(word*)malloc(sizeof(word));//�޸� ���� �Ҵ�(������)
				strcpy(W2->wname,name);
				W2->index=number;
				W1->link=W2;
				W2->link=NULL;//��� �ܾ��, �ε���, ��ũ����
				W1=W2;	//W2�� �޾ƿ� �� ��� �ּҸ� W1�� �ѱ�� ���� �����ֱ⿡�� W2�� �� ��带 �޾ƿ��� ����.
				if(number==1){
					W=W1;//�ε��� �ѹ��� 1�� ���(ù ���) �ּҸ� W�� ����
				}
				
			}
		}
	}	//�ݺ��� ��
	
here:
	a=0;
	WW=W;
	while(1){	//�˻� �ݺ���
		printf("\n�˻��� �ܾ�: ");
		scanf("%s",wordname);
		printf("�˻��� �ܾ��� ����Ʈ ���� index�� ");
		while(1){
			if(strcmp(wordname,WW->wname)==0){
				a++;//�˻���� ���ܾ ��ġ�� �� �ߺ��� ����
				printf("%d ",WW->index);//�ε��� ���
			}
			WW=WW->link;
			if(WW==NULL)break;//������ ��带 ���� NULL�� ���� �� ���� ����
		}
			printf("�� �� %d�� �˻� �Ǿ����ϴ�.",a);
			printf("\n1.�˻� ���\n2.������  ");
			scanf("%d",&b);
			if(b==1)goto here;
			else break;
	}
		//�ݺ��� ��
	
	WW=W;	//���� �޸� �ݳ�
	while(1){
		if(WW->link==NULL){free(WW);break;}
		else{W=WW->link; free(WW); WW=W;}
	}

	fclose(fp);	//���� �ݱ�
}

