#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct word{//단어 노드 구조 선언
	char wname[20];
	int index;
	struct word *link;
}word;

char name[20];//단어 읽어서 노드에 저장하기 위한 임시 저장소.

void main(){
	int a=0;
	int b=-1;
	int number=0;//각 노드 인덱스에 저장하기 위한 변수
	char space=' ';//검색시 공백으로 단어와 단어 사이를 구분짓기 위함.
	char buffer[256];//파일 읽어올 때의 한 스트링.
	word *W,*WW;	//리스트의 첫 노드를 저장하기 위한 포인터
	word *W1;
	word *W2;//동적으로 할당할 메모리 포인터
	FILE *fp=NULL;
	char fname[128];//파일이름을 저장하기 위한 문자열
	char wordname[20];//검색할 단어

	printf("파일이름: ");
	scanf("%s",fname);
	if((fp=fopen(fname,"r"))==NULL)//파일오픈.
	{
		fprintf(stderr,"파일 %s을 열 수 없습니다.",fname);
		exit(1);
	}
	W1=(word*)malloc(sizeof(word));
	W1->link=NULL;
	

	while(fgets(buffer,256,fp)){//단어를 노드로 받아오는 반복문(string 단위로 읽어옴)
		for(int n=0;n<256;n++)
		{
			if((buffer[n]==space)||(buffer[n]==NULL)){//공백을 만나거나 string의 끝을 만나면
				number++;//인덱스 넘버 증가
				for(int m=1;m<=(n-a);m++)name[m-1]=buffer[b+m];//이전 공백 다음 항 부터 다음 공백 이전 항 까지의 buffer[]를 name[]에 복사
				b=n;
				a=b+1;
				W2=(word*)malloc(sizeof(word));//메모리 동적 할당(노드생성)
				strcpy(W2->wname,name);
				W2->index=number;
				W1->link=W2;
				W2->link=NULL;//노드 단어명, 인덱스, 링크연결
				W1=W2;	//W2로 받아온 새 노드 주소를 W1로 넘기고 다음 루프주기에서 W2에 새 노드를 받아오기 위함.
				if(number==1){
					W=W1;//인덱스 넘버가 1인 노드(첫 노드) 주소를 W에 대입
				}
				
			}
		}
	}	//반복문 끝
	
here:
	a=0;
	WW=W;
	while(1){	//검색 반복문
		printf("\n검색할 단어: ");
		scanf("%s",wordname);
		printf("검색한 단어의 리스트 상의 index는 ");
		while(1){
			if(strcmp(wordname,WW->wname)==0){
				a++;//검색어와 노드단어가 일치할 시 중복수 증가
				printf("%d ",WW->index);//인덱스 출력
			}
			WW=WW->link;
			if(WW==NULL)break;//마지막 노드를 지나 NULL을 만날 시 루프 종료
		}
			printf("로 총 %d개 검색 되었습니다.",a);
			printf("\n1.검색 계속\n2.나가기  ");
			scanf("%d",&b);
			if(b==1)goto here;
			else break;
	}
		//반복문 끝
	
	WW=W;	//동적 메모리 반납
	while(1){
		if(WW->link==NULL){free(WW);break;}
		else{W=WW->link; free(WW); WW=W;}
	}

	fclose(fp);	//파일 닫기
}

