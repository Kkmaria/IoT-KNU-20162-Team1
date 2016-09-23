#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ListNodeType ListNode;
struct ListNodeType
{
	char data[20];         // ���ڿ��� ������ �迭
	ListNode* link;        // ������带 �����ϰ��ִ� ��ũ
};

typedef struct LinkedListType LinkedList;
struct LinkedListType
{
	int currentElementCount;	// ���� ����� ������ ����
	ListNode headerNode;		// ��� ���(Header Node)
};

LinkedList* createLinkedList();
void addNode(LinkedList* pList, ListNode* newNode);
void display(LinkedList* pList);
int compare(char input[],LinkedList* pList );


int main(void)
{
		int count=0;
		char readfile [30]={0,};   // �����̸��� �ޱ����� �迭
		char input [30]={0,};      // �˻��� �ܾ �ޱ����� �迭
		FILE* stream;    // ���� ��Ʈ�� ������ ���� stream ����
		int file_state;  // ������ ���Ḧ ���� ���� üũ ��������
		LinkedList* pList;  
		ListNode* Node;     
			
			if((readfile[0]) == 0)  // �����Է� Ȯ��, �Է��̵��´ٸ� �迭�� ù��°���� 0�� �ƴҰ��̱� ����
				{
					printf("���ϸ��� �Է��Ͻÿ�: ");
					scanf("%s",&readfile);
					printf("\n");
					fflush(stdin); // �Է¹��۸� ����
				}
			
				stream =fopen(readfile,"r");  // ������ �б���� ����

				if( stream == NULL)   // ���Ͻ�Ʈ���� ����� �����Ͽ����� ����
				{
					printf("���Ϻҷ����� ���� �ٽ��Է��Ͻÿ�\n");
				}
				
				else
				{
					pList = createLinkedList();  // ��ũ�帮��Ʈ ����
				}

			while(!feof(stream))  // ������ ������ ���� �����ϴ� �ݺ��� ����
			{
				Node =(ListNode*)malloc(sizeof(ListNode));  // �����Ҵ�
				fscanf(stream,"%s",Node->data);          // ������ ���� ���� ���ڿ��Է��� Node�� data �κп� ���ʷ� ����
				Node->link =NULL;
				addNode(pList, Node);                 // ���ο� ��带 �߰�
			}

			printf("ã�� ���ڸ� �Է��Ͻÿ�: ");
			gets(input);                            // �˻��� ���� ã�� ���ڿ��� �迭�� �Է¹���
			printf("\n");

			//display(pList);                         // ������ ���� ���� ���ڵ��� ����� ����Ʈ�� ����Ǿ��ִ��� Ȯ���غ�
			count= compare(input,pList);              // ����Ʈ�� ����� ���ڿ��� �ϻ��� ���ڸ� ���Ͽ� �˻��� �� ��ŭ ī��Ʈ�� 
		
			printf("�˻��� �ܾ�� �� %d�� �Դϴ�\n",count);
			
			file_state = fclose(stream);                //���Ͻ�Ʈ�� ����
			if(file_state == EOF)
			{
				printf("���ϴݱ� ����");
			}
		
		return 0;
				

	} 

LinkedList* createLinkedList()
{
	LinkedList *pList ;                          // LinkedList�� �޸𸮸� �����Ҵ��ϰ� ���� 
	pList = (LinkedList *)malloc(sizeof(LinkedList));  
	if (pList != NULL) {                                   //�޸��Ҵ�� ������ ����
		memset(pList, 0, sizeof(LinkedList)); //�ʱ�ȭ
		//pList->currentElementCount=0;
		//pList->headerNode.link = NULL;
	}

	else {
		printf("�޸��Ҵ���� createLinkedList()\n");   
		return NULL;
	}

	return pList;
}

void addNode(LinkedList* pList, ListNode* newNode)
{
	ListNode* preNode;
	ListNode* pNewNode;

	preNode = &(pList->headerNode); // prenode�� pList headerNode �ּҸ� ����
	pNewNode= newNode;              // ���ο� ������
	

	if(pList->headerNode.link == NULL)  //����� ��尡 ���°��� üũ
	{
		pNewNode->link = preNode->link;
		preNode->link = pNewNode;
	}
	else{
		while(preNode->link !=NULL)  // ����� ���� ã����
		{		
			preNode = preNode->link;
		}
		preNode->link =pNewNode;
		
	}
}

void display(LinkedList* pList)
{
	ListNode* temp;
	
	temp = pList->headerNode.link;
			for(;temp != NULL ;temp = temp->link)  // NULL �ּҸ� ���� ��ũ�帮��Ʈ�� ���������� �������ݴϴ�
			{
				printf("%s",temp->data);  // data�� ����� ���� ����մϴ�
			}
}

int compare(char input[],LinkedList* pList )
{

	int count=0;
	int n=0;
	ListNode* temp;
	int temp2;
	temp = pList->headerNode.link; 

	for(;temp != NULL ;temp = temp->link)    // NULL �ּҸ� ���� ��ũ�帮��Ʈ�� ���������� �������ݴϴ�
			{
				n=strcmp(temp->data,input);    // strcmp �Լ��� �̿��� ���ڿ��� ����
				temp2=(pList-> currentElementCount)++;   // �ε����� ī��Ʈ��
				if(n==0){                            // strcmp �Լ��� 0�� �����ϸ� �Ȱ��� ���ڿ�
					count++;                         // �˻��� �ܾ��� ���� ī��Ʈ��
					printf("\n%s�� ����Ʈ�� %d��° Index�Դϴ�\n",input,temp2);
				}
				
			}

	if(count==0)
	{
		printf("�˻��� �ܾ �����ϴ�");
	}
	
	return count;
}