#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;              //����ֵ״̬

/*��־
3.29:��ɿ��Ա��¼,���õ�����,��ݸ�ڲ���Ԥ���峤�ȵĴ�ͷ˫����,
ͷ����ſ�ݹ���Ϣ(����,����,��ָ���ַ)
3.30:null
3.31:δ���ȡ����洢,δ��ɸ�ڵ�ȡ��
4.2:�ֻ��ŵ�ȡ��,���Ա��ȡ��,�ֻ����ӱ�Ĳ���
4.6:���,chaos tap mad,δ���:ȡ��������,����
*/

//******************node*****type*************************�˴��������нڵ�����
typedef struct locker_node* locker_pointer; //ָ���ڽڵ��ָ��

//���

struct locker_node {					//�����ڽڵ�
	int num;							//��ں���(ͷ������ܽ����)
	int state;							//����״̬(0/1)(ͷ�������ʹ����)
	locker_pointer prior,next;				//next,prior��
};
//ȡ����
typedef struct code_addr_node* code_addr_pointer;
typedef struct code_node* code_pointer;
typedef struct record_node* record_pointer;
typedef struct phonenum_node* phonenum_pointer;
typedef struct deliverman_node* deliverman_pointer;
typedef struct record_node* record_pointer;
struct stuffs {
	char num[6];						//��Ӧ��Ʒ5λ����
	int iftimeout;						//�Ƿ�ʱ(1/0/-1)-1Ϊȡ��,0����״̬,1��ʱ
	char phonenum[12];					//����
};
struct code_node {
	struct stuffs stuff;
	char code[7];						//ȡ����
	locker_pointer locker_p;					//ָ���ڽڵ�ָ��
	phonenum_pointer  phonenum_p;				//ָ���ֻ�����ڵ�ָ��(����)
	deliverman_pointer deliverman_p;				//ָ����Ա�ڵ�ָ��
	code_pointer prior,next;					
};
struct record_node {//���Ա�ӱ�(��ݼ�¼)
	struct stuffs stuff;
	code_pointer code_p;//��Ʒ��Ӧȡ����ڵ�λ��
	record_pointer next;
};
//�绰����
struct phonenum_node {
	char phonenum[12];					//�������11λ����
	int amount;							//����ú���洢�Ŀ������
	code_addr_pointer sublist_front,sublist_rear,sublist_prior;			//�����ӱ�ͷָ��
	phonenum_pointer prior,next;				//����next��
};
struct code_addr_node {//����ȡ�����ַ�Ľڵ�,���ֻ��Ź������ӱ�Ԫ��
	code_pointer code_P;
	code_addr_pointer  next;
};
//���Ա��Ϣ
struct deliverman_node
{
	char Dname[10];						//���Ա����
	char Dphonenum[12];					//���Ա�绰����
	char Dcode[7];						//���Ա����
	char psw[7];					//���Ա����
	record_pointer sublist;		//���Ա��������Ʒ��Ϣ(����)
	deliverman_pointer next;		//����next��
};




//�����������
typedef struct locker_node* locker_list;//������˫�������� ���
typedef struct deliverman_node* deliverman_list;//������Ա�����
typedef struct code_node* code_list;//����ȡ��������
typedef struct phonenum_node* phonenum_list;//�����ֻ��Ź����


//��������
deliverman_list init_deliverman_list();
code_list  init_code_list();
phonenum_list init_phonenum_list();
locker_list init_locker_list(int start, int end);
Status insert_deliverman_list(deliverman_list head, struct deliverman_node* node);
Status insert_locker_list(locker_list head);
Status insert_phonenum_list(phonenum_list head, struct phonenum_node* node);
Status insert_code_list(code_list list, struct code_node* node);
deliverman_pointer locate_deliverman_list(deliverman_list head, char Dcode[7]);
phonenum_pointer locate_phonenum_list(phonenum_list head, char phonenum[12]);
code_pointer locate_code_list(code_list list, char code[7]);
Status de_locker_list(locker_list head, locker_pointer node);
Status de_code_list(code_list list, code_pointer f);
Status put_stuff(code_list cL, deliverman_list dL, locker_list lL, phonenum_list pL,struct stuffs stuff);
Status get_stuff(code_list cL, deliverman_list dL, locker_list lL, phonenum_list pL,struct stuffs stuff);
Status sign_up(deliverman_list list);
Status sign_in(deliverman_list list,deliverman_pointer p);
int main()
{
	/*��Ԥ�����������Ա����ӵ��ڴ�*/
	deliverman_list DL = init_deliverman_list();//��ʼ���������
	locker_list lockers_L= init_locker_list(1,5);//����������ͬ�Ŀ�ݹ�˫��
	locker_list lockers_M= init_locker_list(6,14);
	locker_list lockers_S= init_locker_list(15,24);
	code_list cL = init_code_list();
	phonenum_list pL = init_phonenum_list();
	
	deliverman_pointer D1 = (deliverman_pointer)malloc(sizeof(struct deliverman_node));
	deliverman_pointer D2 = (deliverman_pointer)malloc(sizeof(struct deliverman_node));


	strcpy(D1->Dname, "����");
	strcpy(D1->Dcode, "000001");
	strcpy(D1->Dphonenum, "13927367681");
	strcpy(D1->psw, "000001");


	strcpy(D2->Dname, "����");
	strcpy(D2->Dcode, "000002");
	strcpy(D2->Dphonenum, "13565741386");
	strcpy(D2->psw, "000002");
	/*�����Ա��������*/
	insert_deliverman_list(DL, D1);
	insert_deliverman_list(DL, D2);
	//printf("%s\n", DL->next->next->Dname);
	//************************************************************************���Ͼ�Ϊ��������
	while (1)
	{
		char i;
		printf("��ӭʹ�ø�ڵݹ�\n");
		printf("��ѡ����:���빦�����\n");
		printf("1.ȡ���\n");
		printf("2.����Աģʽ\n");
		scanf("%c", &i);//��ȡ�����ַ�
		getchar();
		if (i == '1')//�û��ӿ�
		{
			printf("1.ȡ���\n");
			printf("2.������һ��\n");
			scanf("%c",&i);
			getchar();
		}
		else if (i == '2')//����Ա�ӿ�
		{
			while (1)
			{
				printf("1.��¼\n");
				printf("2.ע��\n");
				printf("3.������һ��\n");
				scanf("%c", &i);
				if (i == '1')
				{
					struct deliverman_node d;
					deliverman_pointer dP = &d;
					if (sign_in(DL,dP) == TRUE)//��¼�ɹ�
					{
						getchar();
						printf("��¼�ɹ�\n");
						while (1) 
						{
							/*���Ա����*/
							printf("1.Ͷ�ݿ��\n");
							printf("2.ȡ�����\n");
							printf("3.��ѯ��ݹ�״̬\n");
							printf("4.��ѯ��Ͷ�ݿ��״̬\n");
							printf("5.������ҳ\n");
							scanf("%c", &i);
							getchar();
							if (i == '1')
							{
								struct stuffs stuff;
								stuff.iftimeout = -1;
								printf("��ȡ�����Ϣ\n");
								printf("�����ݵ���\n");
								scanf("%s",stuff.num);
								printf("�����ݺ���\n");
								scanf("%s", stuff.phonenum);
								printf("��ѡ���ڴ�С(S/M/L)\n");
								getchar();
								scanf("%c", &i);
								getchar();
								switch (i)
								{
								case 'S':put_stuff(cL,dP,lockers_S,pL,stuff); break;
								case 'M':put_stuff(cL, dP, lockers_M, pL, stuff); break;
								case 'L':put_stuff(cL, dP, lockers_L, pL, stuff); break;
								default:
									printf("�������,�������������һ��\n");
									getchar();
									continue;
								}
								printf("Ͷ�ݳɹ�!\n");
								printf("���͵���Ϣ\n");
							}
							else if (i == '2')
							{
								printf("2����������\n");
								printf("�������������һ��\n");
								getchar();
								continue;
							}
							else if (i == '3')
							{

								printf("��ǰ��ݹ�״̬\n");
								printf("��ǰ��Ź�����%d/%d\n",lockers_L->state,lockers_L->num);
								printf("��ǰ�кŹ�����%d/%d\n",lockers_M->state, lockers_M->num);
								printf("��ǰС�Ź�����%d/%d\n",lockers_S->state, lockers_S->num);
								printf("�������������һ��\n");
								getchar();
								continue;
							}
							else if (i == '4')
							{
								printf("4����������\n");
								printf("�������������һ��\n");
								getchar();
								continue;
							}
							else if (i == '5')
							{
								break;
							}
							else
							{
								printf("�������,�����������ѡ��\n");
								getchar();
								continue;
							}
						}						
					}
					else//�����������
					{
						printf("�����������˺Ų�����!�������������һ��\n");
						getchar();
						continue;
					}
					break;
				}
				else if (i == '2')
				{
					if (sign_up(DL)==TRUE)
					{
						printf("ע��ɹ�!�������������һ�����µ�¼\n");
						getchar();
						continue;
					}
					else
					{
						printf("������֤����!�������������һ��\n");
						getchar();
						continue;
					}
				}
				else if (i == '3')
				{
					break;
				}
				else
				{
					printf("ѡ�����������ѡ��!\n");
					continue;
				}
			}
		}
		else
		{
			printf("������󣡣� �����������������\n");
			continue;
		}
	}
	return 0;
}
//************************************************************************��������Ԥ��
void preinstall()
{


}
//************************************************************************��ʼ��
deliverman_list init_deliverman_list() {							//��ʼ�����Ա����
	deliverman_pointer head;
	head = (deliverman_list)malloc(sizeof(struct deliverman_node));
	head->next = NULL;
	return head;
}
code_list  init_code_list() {	//��ʼ��ȡ��������
	code_pointer  head;
	head = (struct code_node*)malloc(sizeof(struct code_node));
	head->next = NULL;
	head->prior = head;//ͷ���prior�洢rear
	return head;
}
phonenum_list init_phonenum_list() 
{
	phonenum_list  head;
	head = (phonenum_list)malloc(sizeof(struct phonenum_node));
	head->next =NULL;
	head->sublist_front = head->sublist_rear = NULL;
	head->prior = head;//ͷ���ָ��rear
	return head;
}
locker_list init_locker_list(int start,int end)								//��ʼ����ݹ�,�����ݹ񳤶�
{
	int i;
	if (start > end)
	{
		printf("��ֵ�������");
		exit(0);
	}
	locker_pointer head,p,s;//pΪ��ǰ�½ڵ��ַ,sΪ�������ڵ�����ַ
	head =s= (locker_pointer)malloc(sizeof(struct locker_node));//���ɹ������ͷ���
	head->next =  NULL;
	head->prior = head;//ͷ���ǰ����ַ��ŵ�ǰָ����ָλ��
	head->num = end-start+1;//�洢�������Ľڵ�����
	head->state = 0;//����Ѵ洢��
	for (i = start; i <= end; i++)
	{
		p = (locker_pointer)malloc(sizeof(struct locker_node));
		p->next = NULL;
		p->num = i ;//��ʼ��ݸ�ں���
		p->state = 0;//Ĭ��״̬Ϊ�ر�״̬
		p->prior = s;
		s->next = p;	
		s = p;
	}
	return head;
}
//************************************************************************��������
Status insert_deliverman_list(deliverman_list head, struct deliverman_node* node) {//���ڿ��Ա����Ĳ���/ע�᷽��
	deliverman_pointer p = node;			//pָ��ָ��node	
	p->sublist = NULL;
	p->next = head->next;					//ͷ�巨������
	head->next = p;
	return OK;
}
Status insert_locker_list(locker_list head) {//���ڿ�ݹ������Ʒ����,addr���ط�����ӵ�ַ
	locker_pointer p = head->prior;

	if (p->next==NULL) {//��pָ���������һλ,��˵���������
		return ERROR;
	}
	p = p->next;//����ƶ�
	p->state = 1;//�ı���״̬
	head->state++;//������һ
	head->prior = p;//������µĵ�ַ
	return OK;
}
Status insert_phonenum_list(phonenum_list head, struct phonenum_node* node)//����ȡ���˿͵ĺ���ڵ�Ĵ洢
{
	node->next = NULL;
	code_addr_pointer head1;
	head1 = (code_addr_pointer)malloc(sizeof(struct code_addr_node));
	head1->next = NULL;
	head1->code_P = NULL;
	node->sublist_front = head1;//�ӱ�ͷ�ڵ�
	phonenum_pointer p = node;			//pָ��ָ��node	
	phonenum_pointer rear = head->prior;
	rear->next=node;//���������
	node->prior = rear;
	head->prior = node;
	return OK;
}
Status insert_code_list(code_list head, struct code_node* node)//����ȡ����Ĵ洢
{
	code_pointer p = node;
	node->next = NULL;
	code_pointer rear = head->prior;
	rear->next = node;//���������
	node->prior = rear;
	head->prior = node;
	return OK;
}
Status insert_code_addr_list(phonenum_pointer p, struct code_addr_node* node)
{
	p->sublist_rear->next=node;//β�巨
	p->sublist_rear = node;
	p->amount++;
	return OK;
}
Status insert_record_list(deliverman_pointer head,struct code_node* node) //���Ա�ӱ�Ĳ���
{
	record_pointer p;
	p = (record_pointer)malloc(sizeof(struct record_node));
	p->code_p=node;
	p->stuff = node->stuff;
	p->next=head->sublist;
	head->sublist = p;
	return OK;
}
//*************************************************************************��������
deliverman_pointer locate_deliverman_list(deliverman_list head, char Dcode[7]) {//��¼���ҹ���,����Ա���ڵ�ǰ����ַ
	deliverman_pointer p;
	p = head;
	while (p->next != NULL)
	{
		if (strcmp(p->next->Dcode, Dcode) == 0)
			break;
		else
			p = p->next;
	}
	return p;
}
phonenum_pointer locate_phonenum_list(phonenum_list head,char phonenum[12])//�������,����,���غ������ڵ�ַ
{
	phonenum_pointer p;
	p = head->next;
	while (p->next != NULL)
	{
		if (strcmp(p->phonenum, phonenum) == 0)
			break;
		else
			p = p->next;
	}
	return p;
}
code_pointer locate_code_list(code_list head, char code[7]) {//����ȡ����,����,���Ҷ�Ӧȡ�����ȡ����ڵ��ַ
	code_pointer p=head->next;
	while (p != NULL)
	{
		if (strcmp(p->code, code) == 0)
			break;
		else
			p = p->next;
	}
	return p;//���ض�Ӧ�ڵ��ַ
}
code_pointer locate_code_addr_list(phonenum_pointer node, char code[7]) {//�����������ѯ
	code_addr_pointer p = node->sublist_front;
	while (p->next != NULL)
	{
		if (strcmp(p->next->code_P->code, code))
			break;
		else
			p = p->next;
	}
	node->sublist_prior = p;//��Ӧ�ڵ��ǰ���ڵ�,����ɾ��
	return p->next->code_P;//���ض�Ӧ�ڵ�
}

//*********************************************************************�����ȡ��
Status de_locker_list(locker_list head, locker_pointer node) {//���ȡ����Ʒ���ں��Ƶ���ָ��λ��,�������ٴ���
	if (head->next == NULL)
	{
		printf("����;");//����ȫ����,��ֹ����Ұָ��
		return ERROR;
	}
	locker_pointer p = head->prior;
	node->prior->next = node->next;
	node->next->prior = node->prior;//ȡ��node�ڵ�
	node->next = p->next;//node�ڵ�ָ��ǰ�ڵ��next
	node->prior = p;//node�ڵ�ǰ��ָ��ǰ�ڵ�
	p->next = node;
	node->next->prior = p;
	return OK;
}
Status de_code_list(code_list head, code_pointer p)//ȡ��ȡ����,pΪȡ���ڵ��ַ
{
	code_pointer rear = head->prior;
	if (rear == head)
	{
		printf("����;");
		return ERROR;
	}
	else if (p->next == NULL)
	{
		head->prior = p->prior;//��ɾ���ڵ�Ϊβ���,��β���ָ��ָ��ͷ���
	}
	else
	{
		p->prior->next=p->next;//�Ƴ�ǰ����ָ��
		p->next->prior = p->prior;
	}
	return OK;
}
Status de_phonenum_list(phonenum_list head, phonenum_pointer p)//ȡ���ֻ��Žڵ�
{
	phonenum_pointer rear = head->prior;
	if (rear == head)
	{
		printf("����;");
		return ERROR;
	}
	else if (p->next == NULL)
	{
		head->prior = p->prior;//��ɾ���ڵ�Ϊβ���,��β���ָ��ָ��ͷ���
	}
	else
	{
		p->prior->next = p->next;//�Ƴ�ǰ����ָ��
		p->next->prior = p->prior;
	}
	return OK;
}
Status de_deliverman_list(deliverman_list head, deliverman_pointer f) {//ȡ�����Ա�ڵ�,fΪ���Աǰ�����
	if (head->next==NULL) 
	{
		printf("����;");
		return ERROR;
	}
	deliverman_pointer p = f->next;
	f->next = p->next;
	return OK;
}
Status de_code_addr_list(phonenum_pointer node, code_addr_pointer f) {//ȡ������ڵ���ӱ��нڵ�()
	if (node->sublist_front->next== NULL)
	{
		printf("������;");
		return ERROR;
	}
	code_addr_pointer p = f->next;
	f->next = p->next;
	return OK;
}
//**********************************************************************************��������
void create_code(char *Scode)//���������6λȡ����
{
	int code;
	srand((unsigned)time(NULL));
	code = rand() % (999999 - 100000 + 1) + 100000;
	_itoa(code, Scode, 10);
}
Status sign_in(deliverman_list list,deliverman_pointer p) {//��¼
	char Dcode[7], psw[7];
	printf("�˻�(����):");
	scanf("%s", Dcode);
	printf("����:");
	scanf("%s", psw);
	p = locate_deliverman_list(list, Dcode);//���������п��Ա�ڵ�,����ǰ���ڵ�
	if (strcmp(p->next->psw, psw) == 0)//��¼�ɹ�
		return TRUE;
	else
		return FALSE;

}
Status sign_up(deliverman_list list) {//ע��
	char  psw2[7];
	struct deliverman_node n;
	printf("�˻�(����):\n");
	scanf("%s", n.Dcode);
	printf("�ֻ���:\n");
	scanf("%s", n.Dphonenum);
	printf("����:\n");
	scanf("%s", n.Dname);
	printf("����:\n");
	scanf("%s", n.psw);
	printf("�ٴ�ȷ������:\n");
	scanf("%s", psw2);
	if (strcmp(n.psw, psw2) == 0)
	{
		insert_deliverman_list(list, &n);
		return TRUE;
	}
	else
		return FALSE;
}
//******************************************************************************************���ϲ���(��ȡ)
Status get_stuff(code_list cL,deliverman_pointer dP,locker_list lL,phonenum_list pL, struct stuffs stuff) {//ȡ��(dLΪ��ǰ���Ա�Ľڵ�)

	return OK;
}
Status put_stuff(code_list cL, deliverman_pointer dP, locker_list lL, phonenum_list pL, struct stuffs stuff) {//Ͷ��
	code_pointer cP;
	phonenum_pointer pP;
	code_addr_pointer caP;
	cP = (code_pointer)malloc(sizeof(struct code_node));//�½�ȡ����ڵ�
	caP = (code_addr_pointer)malloc(sizeof(struct code_addr_node));//�����ڵ�
	char Scode[7];
	/*���ڸ�ڵĲ���*/
	if(insert_locker_list(lL)==ERROR);//�Զ�������,����(����)����ĸ�ڵ�ַ
		return FALSE;//���������ʧ��
   /*���ں���Ĳ���*/
	pP = locate_phonenum_list(pL, stuff.phonenum);
	if (pP == NULL)//�����������ڸú���,Ϊ�º���
	{
		pP = (phonenum_pointer)malloc(sizeof(struct phonenum_node));
		strcpy(pP->phonenum, stuff.phonenum);
		insert_phonenum_list(pL, pP);//�����ֻ���
	}
	/*����ȡ����Ĳ���*/
	create_code(Scode);
	strcpy(cP->code,Scode );//����ȡ���벢д��ȡ����ڵ�
	cP->stuff = stuff;
	cP->locker_p = lL->prior;//�������ĸ�ڵ�ַ
	cP->phonenum_p = pP;//����绰�ŵ�ַ
	cP->deliverman_p = dP;//������Ա��ַ
	/*����ȡ��������������*/
	caP->code_P = cP;
	/*�ڵ�������*/
	insert_code_list(cL, cP);//����ȡ����
	insert_code_addr_list(pP,caP);//��������
	insert_record_list(dP,cP);//�����¼
}