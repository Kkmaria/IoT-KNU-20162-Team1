#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ListNodeType ListNode;
struct ListNodeType
{
	char data[20];         // 문자열을 저장할 배열
	ListNode* link;        // 다음노드를 연결하고있는 링크
};

typedef struct LinkedListType LinkedList;
struct LinkedListType
{
	int currentElementCount;	// 현재 저장된 원소의 개수
	ListNode headerNode;		// 헤더 노드(Header Node)
};

LinkedList* createLinkedList();
void addNode(LinkedList* pList, ListNode* newNode);
void display(LinkedList* pList);
int compare(char input[],LinkedList* pList );


int main(void)
{
		int count=0;
		char readfile [30]={0,};   // 파일이름을 받기위한 배열
		char input [30]={0,};      // 검색할 단어를 받기위한 배열
		FILE* stream;    // 파일 스트림 포인터 변수 stream 선언
		int file_state;  // 파일의 종료를 위한 상태 체크 변수선언
		LinkedList* pList;  
		ListNode* Node;     
			
			if((readfile[0]) == 0)  // 파일입력 확인, 입력이들어온다면 배열의 첫번째값이 0아 아닐것이기 때문
				{
					printf("파일명을 입력하시오: ");
					scanf("%s",&readfile);
					printf("\n");
					fflush(stdin); // 입력버퍼를 비운다
				}
			
				stream =fopen(readfile,"r");  // 파일을 읽기모드로 연다

				if( stream == NULL)   // 파일스트림이 제대로 동작하였는지 점검
				{
					printf("파일불러오기 실패 다시입력하시오\n");
				}
				
				else
				{
					pList = createLinkedList();  // 링크드리스트 생성
				}

			while(!feof(stream))  // 파일이 끝날때 까지 실행하는 반복문 설정
			{
				Node =(ListNode*)malloc(sizeof(ListNode));  // 동적할당
				fscanf(stream,"%s",Node->data);          // 파일을 통해 받은 문자열입력을 Node의 data 부분에 차례로 저장
				Node->link =NULL;
				addNode(pList, Node);                 // 새로운 노드를 추가
			}

			printf("찾을 문자를 입력하시오: ");
			gets(input);                            // 검색을 통해 찾을 문자열을 배열로 입력받음
			printf("\n");

			//display(pList);                         // 파일을 통해 받은 문자들이 제대로 리스트에 저장되어있는지 확인해봄
			count= compare(input,pList);              // 리스트에 저장된 문자열과 겅색한 문자를 비교하여 검색된 수 만큼 카운트함 
		
			printf("검색된 단어는 총 %d개 입니다\n",count);
			
			file_state = fclose(stream);                //파일스트림 닫음
			if(file_state == EOF)
			{
				printf("파일닫기 에러");
			}
		
		return 0;
				

	} 

LinkedList* createLinkedList()
{
	LinkedList *pList ;                          // LinkedList형 메모리를 동적할당하고 점검 
	pList = (LinkedList *)malloc(sizeof(LinkedList));  
	if (pList != NULL) {                                   //메모리할당시 오류를 점검
		memset(pList, 0, sizeof(LinkedList)); //초기화
		//pList->currentElementCount=0;
		//pList->headerNode.link = NULL;
	}

	else {
		printf("메모리할당오류 createLinkedList()\n");   
		return NULL;
	}

	return pList;
}

void addNode(LinkedList* pList, ListNode* newNode)
{
	ListNode* preNode;
	ListNode* pNewNode;

	preNode = &(pList->headerNode); // prenode에 pList headerNode 주소를 넣음
	pNewNode= newNode;              // 새로운 노드생성
	

	if(pList->headerNode.link == NULL)  //연결된 노드가 없는것을 체크
	{
		pNewNode->link = preNode->link;
		preNode->link = pNewNode;
	}
	else{
		while(preNode->link !=NULL)  // 노드의 끝을 찾으면
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
			for(;temp != NULL ;temp = temp->link)  // NULL 주소를 만나 링크드리스트가 끝날때까지 실행해줍니다
			{
				printf("%s",temp->data);  // data에 저장된 값을 출력합니다
			}
}

int compare(char input[],LinkedList* pList )
{

	int count=0;
	int n=0;
	ListNode* temp;
	int temp2;
	temp = pList->headerNode.link; 

	for(;temp != NULL ;temp = temp->link)    // NULL 주소를 만나 링크드리스트가 끝날때까지 실행해줍니다
			{
				n=strcmp(temp->data,input);    // strcmp 함수를 이용해 문자열비교 실행
				temp2=(pList-> currentElementCount)++;   // 인덱스를 카운트함
				if(n==0){                            // strcmp 함수가 0을 리턴하면 똑같은 문자열
					count++;                         // 검색된 단어의 수를 카운트함
					printf("\n%s는 리스트의 %d번째 Index입니다\n",input,temp2);
				}
				
			}

	if(count==0)
	{
		printf("검색된 단어가 없습니다");
	}
	
	return count;
}