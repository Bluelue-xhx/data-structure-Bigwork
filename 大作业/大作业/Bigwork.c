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

struct locker_node
{					//�����ڽڵ�
	int num;							//��ں���(ͷ������ܽ����)
	int state;							//����״̬(0/1)(ͷ�������ʹ����)
	locker_pointer prior,next,head;				//next,prior��
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
	record_pointer record_p;						//ָ���Լ��ı��ݽڵ�
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
	code_addr_pointer sublist_head,sublist_prior;			//�����ӱ�ͷָ��
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
Status put_stuff(code_list cL, deliverman_pointer dP, locker_list lL, phonenum_list pL, struct stuffs stuff,int size);
Status get_stuff(code_list cL, phonenum_list pL, char code[7], int mode);
Status sign_up(deliverman_list list);
Status sign_in(deliverman_list list,deliverman_pointer *p);
void see(code_list cL, deliverman_list dL, locker_list lL, phonenum_list pL);
void print_Dhistory(deliverman_pointer dp);
code_pointer locate_record_list(deliverman_pointer dp, char num[6]);
int main()
{
	/*��Ԥ�����������Ա����ӵ��ڴ�*/

	deliverman_list DL = init_deliverman_list();//��ʼ���������
	locker_list lockers_L = init_locker_list(1, 5);//����������ͬ�Ŀ�ݹ�˫��
	locker_list lockers_M = init_locker_list(6, 14);
	locker_list lockers_S = init_locker_list(15, 24);
	code_list cL = init_code_list();
	phonenum_list pL = init_phonenum_list();

	deliverman_pointer D1 = (deliverman_pointer)malloc(sizeof(struct deliverman_node));
	deliverman_pointer D2 = (deliverman_pointer)malloc(sizeof(struct deliverman_node));
	struct stuffs stuff1;
	struct stuffs stuff2;
	struct stuffs stuff3;
	strcpy(stuff1.num, "11111");
	strcpy(stuff1.phonenum, "12345678909");
	stuff1.iftimeout = -1;
	strcpy(stuff2.num, "22222");
	strcpy(stuff2.phonenum, "12345678909");
	stuff2.iftimeout = -1;
	strcpy(stuff3.num, "33333");
	strcpy(stuff3.phonenum, "12343432343");
	stuff3.iftimeout = -1;

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
	put_stuff(cL, D1, lockers_S, pL, stuff1, 1);
	put_stuff(cL, D2, lockers_S, pL, stuff2, 1);
	put_stuff(cL, D1, lockers_S, pL, stuff3, 1);
	//************************************************************************���Ͼ�Ϊ��������
	while (1)
	{
		int i; char c; char code[7];
		printf("��ӭʹ�ø�ڵݹ�\n");
		printf("��ѡ����:���빦�����\n");
		printf("1.ȡ���\n");
		printf("2.����Աģʽ\n");
		scanf("%d", &i);//��ȡ�����ַ�
		if (i == 1)//�û��ӿ�
		{
			printf("1.ȡ���\n");
			printf("2.������һ��\n");
			scanf("%d", &i);
			getchar();
			if (i == 1)
			{
				do {
					printf("������ȡ����:");
					scanf("%s", code);
					getchar();
				} while (get_stuff(cL, pL, code, 0) == TRUE);//0����Ϊ�ͻ�ģʽ,����ture����ȡ��
				continue;//ȡ����ɷ�����һ��
			}
		}
		else if (i == 2)//����Ա�ӿ�
		{
			while (1)
			{
				printf("1.��¼\n");
				printf("2.ע��\n");
				printf("3.������һ��\n");
				scanf("%d", &i);
				if (i == 1)
				{
					deliverman_pointer dP;//˫��ָ��
					if (sign_in(DL, &dP) == TRUE)//��¼�ɹ�
					{
						printf("��¼�ɹ�\n");
						while (1)
						{
							/*���Ա����*/
							printf("1.Ͷ�ݿ��\n");
							printf("2.��ѯ��ݹ�״̬\n");
							printf("3.��ѯ���״̬(ȡ��)\n");
							printf("4.���Դ���\n");
							printf("5.������ҳ\n");
							scanf("%d", &i);
							if (i == 1)
							{
								struct stuffs stuff;
								stuff.iftimeout = -1;
								printf("��ȡ�����Ϣ\n");
								printf("�����ݵ���\n");
								scanf("%s", stuff.num);
								printf("�����ݺ���\n");
								scanf("%s", stuff.phonenum);
								printf("��ѡ���ڴ�С(S/M/L)\n");
								getchar();
								scanf("%c", &c);
								printf("��ʱ��ƷΪ:%s,%s\n", stuff.num, stuff.phonenum);
								switch (c)
								{
								case 'S':put_stuff(cL, dP, lockers_S, pL, stuff, 1); break;//���һ��Ϊ��С
								case 'M':put_stuff(cL, dP, lockers_M, pL, stuff, 2); break;
								case 'L':put_stuff(cL, dP, lockers_L, pL, stuff, 3); break;
								default:
									printf("�������,�������������һ��\n");
									continue;
								}
								printf("Ͷ�ݳɹ�!\n");
								printf("************�ռ���*************\n");
								printf("���Ŀ�ݵ���:%s �ѵ���ڿ�ݹ�\n�鷳����ȡһ��,ȡ����:%sлл,\n", stuff.num, code);
								printf("���Ա�ֻ�%s\n", dP->Dphonenum);
								printf("*************end**************\n");
							}
							else if (i == 2)
							{

								printf("��ǰ��ݹ�״̬\n");
								printf("��ǰ��Ź�����%d/%d\n", lockers_L->state, lockers_L->num);
								printf("��ǰ�кŹ�����%d/%d\n", lockers_M->state, lockers_M->num);
								printf("��ǰС�Ź�����%d/%d\n", lockers_S->state, lockers_S->num);
								printf("�������������һ��\n");
								getchar();
								continue;
							}
							else if (i == 3)
							{
								char num[6];
								code_pointer cP;
								int s;
								print_Dhistory(dP);
								printf("�Ƿ�ȡ�����(y/n),n������һ��\n");
								getchar();
								scanf("%c", &c);
								getchar();
								if (c == 'y')
								{
									while (1)
									{
										printf("������ȡ����Ʒ�ĵ���\n");
										scanf("%s", num);
										getchar();
										cP = locate_record_list(dP, num);
										if (cP == NULL)//�������,����Ʒ�ѱ�ȡ��
										{
											printf("�������,�����Ʒ�ѱ�ȡ��,��������\n");
											continue;
										}
										else
										{
											s = get_stuff(cL, pL, cP->code, 1);
											printf("************�ռ���*************\n");
											printf("���Ŀ�ݵ���:%s�ѱ� \n", num);
											printf("���Ա:%sȡ��\n", dP->Dphonenum);
											printf("*************end**************\n");
											if (s == TRUE)
												continue;
											else
												break;
										}
									}
									continue;
								}
								else if (c == 'n')
									continue;
								printf("�������������һ��\n");
								getchar();
								getchar();
								continue;
							}
							else if (i == 4)
							{
								see(cL, DL, lockers_S, pL);
							}
							else if (i == 5)
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
					else//�����������/�˻�������
					{
						printf("�����������˺Ų�����!������һ�����µ�¼��ע��\n");
						getchar();
						continue;
					}
					break;
				}
				else if (i == 2)
				{
					if (sign_up(DL) == TRUE)
					{
						printf("ע��ɹ�!������һ�����µ�¼\n");
						continue;
					}
					else
					{
						printf("������֤����!�������������һ��\n");
						getchar();
						continue;
					}
				}
				else if (i == 3)
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
//************************************************************************�������ݲ鿴
void see(code_list cL, deliverman_list dL, locker_list lL, phonenum_list pL)
 {
	code_pointer cP = cL;
	deliverman_pointer dP = dL;
	locker_pointer lP = lL;
	phonenum_pointer pP = pL;
	printf("��ǰ���Ա����״̬:");
	while (dP->next != NULL) {
		printf("%s->",dP->next->Dphonenum);
		dP = dP->next;
	}
	printf("\n");
	printf("��ǰȡ��������Ӧ����������״̬:");
	while (cP->next != NULL) {
		printf("%s->",cP->next->code);
		cP = cP->next;
	}
	printf("\n");
	printf("��ǰ��ݹ�״̬:");
	while (lP->next != NULL) {
		printf("%d->", lP->next->num);
		lP = lP->next;
	}
	printf("\n");
	printf("��ǰ�ͻ�����״̬:");
	while (pP->next != NULL) {
		printf("%s->", pP->next->phonenum);
		pP = pP->next;
	}
	printf("\n");
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
	head->sublist_head = NULL;
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
	head->head = head;//ͷ����ͷָ������ͷ����ַ
	head->num = end-start+1;//�洢�������Ľڵ�����
	head->state = 0;//����Ѵ洢��
	for (i = start; i <= end; i++)
	{
		p = (locker_pointer)malloc(sizeof(struct locker_node));
		p->next = NULL;
		p->num = i ;//��ʼ��ݸ�ں���
		p->state = 0;//Ĭ��״̬Ϊ�ر�״̬
		p->head = head;//ÿ���ڵ������ͷָ����
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
	
	code_addr_pointer head1;
	node->next = NULL;
	head1 = (code_addr_pointer)malloc(sizeof(struct code_addr_node));
	head1->next = NULL;
	head1->code_P= NULL;
	node->sublist_head = head1;//�ӱ�ͷ�ڵ�
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
	code_addr_pointer head = p->sublist_head;
	node->next=head->next;//ͷ�巨
	head->next = node;
	return OK;
}
Status insert_record_list(deliverman_pointer head,struct code_node* node) //���Ա�ӱ�Ĳ���
{
	record_pointer p;
	p = (record_pointer)malloc(sizeof(struct record_node));
	p->code_p=node; 
	node->record_p = p;
	p->stuff = node->stuff;
	p->next=head->sublist;
	head->sublist = p;
	return OK;
}
//*************************************************************************��������
deliverman_pointer locate_deliverman_list(deliverman_list head, char Dcode[7]) {//��¼���ҹ���,����Ա���ڵ�ǰ����ַ
	deliverman_pointer p=head;
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
	phonenum_pointer p=head->next;
	while (p != NULL)
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
code_pointer locate_code_addr_list(phonenum_pointer node, char code[7]) {//�����������ѯ(���ѯ���Ľڵ��ǰ���������phonenum��sublist_prior)
	code_addr_pointer p = node->sublist_head;
	while (p->next != NULL)
	{
		if (strcmp(p->next->code_P->code, code)==0)
			break;
		else
			p = p->next;
	}
	if (p->next == NULL)//���������ڸýڵ�
	{
		node->sublist_prior = NULL;//�����ǰ���ڵ�
		return NULL;
	}
	node->sublist_prior = p;//��Ӧ�ڵ��ǰ���ڵ�,����ɾ��
	return p->next->code_P;//���ض�Ӧ�ڵ�
}
code_pointer locate_record_list(deliverman_pointer dp,  char num[6])//ͨ�����ҵ���ȡ������Ͷ
{
	record_pointer rp = dp->sublist;
	while (rp != NULL)
	{
		if (strcmp(rp->stuff.num, num) == 0)//�ҳ���¼
			return rp->code_p;
		rp = rp->next;
	}
	return NULL;//û�д˵���,������������
}

/********************************************************�����ȡ��*************/
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
		p->prior->next = NULL;
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
	if (node->sublist_head->next== NULL)
	{
		printf("������;");
		return ERROR;
	}
	code_addr_pointer p = f->next;
	f->next = p->next;
	return OK;
}
/*********************************************************************************��������*/
void create_code(code_list head, char *Scode,int size)//������������ظ�6λȡ����,��ݹ��С
{
	int code;
	srand((unsigned)time(NULL));
	code_pointer p;
	while (1) {
		code = size*100000+rand() % (99999 - 10000 + 1) + 10000;//ȡ�����һλ������ݴ�С
		_itoa(code, Scode, 10);//intתΪstring
		p = locate_code_list(head,Scode);
		if (p == NULL) //˵�����ظ���
			break;
	}
}
Status sign_in(deliverman_list list,deliverman_pointer *p) {//��¼
	char Dcode[7], psw[7];
	deliverman_pointer p1;
	printf("�˻�(����):");
	scanf("%s", Dcode);
	printf("����:");
	scanf("%s", psw);
	p1 = locate_deliverman_list(list, Dcode);//���������п��Ա�ڵ�,����ǰ���ڵ�
	if (p1->next == NULL)
		return FALSE;//�˻�������
	printf("%s",p1->next->Dcode);
	if (strcmp(p1->next->psw, psw) == 0)//��¼�ɹ�
	{
		p1 = p1->next;
		*p = p1;
		return TRUE;
	}
	else
		return FALSE;//
}
Status sign_up(deliverman_list list) {//ע��
	char  psw2[7];
	deliverman_pointer D = (deliverman_pointer)malloc(sizeof(struct deliverman_node));
	printf("�˻�(����):\n");
	scanf("%s", D->Dcode);
	printf("�ֻ���:\n");
	scanf("%s", D->Dphonenum);
	printf("����:\n");
	scanf("%s", D->Dname);
	printf("����:\n");
	scanf("%s", D->psw);
	printf("�ٴ�ȷ������:\n");
	scanf("%s", psw2);
	if (strcmp(D->psw, psw2) == 0)
	{
		insert_deliverman_list(list, D);
		return TRUE;
	}
	else
		return FALSE;
}
void print_Dhistory(deliverman_pointer dp) {
	record_pointer p = dp->sublist;
	int i;
	printf("״̬(-1ȡ��,0�ڹ�,1��ʱ)\n");
	printf("���    ��Ʒ����   ״̬\n");
	for (i = 1; p != NULL; i++)
	{
		printf("%-2d      %-6s      %-2d\n",i,p->stuff.num,p->stuff.iftimeout);
		p = p->next;
	}
}
/******************************************************************************************���ϲ���(��ȡ)*/
Status get_stuff(code_list cL,phonenum_list pL,	char code[7],int mode) {//ȡ��pLΪ�Ե绰�����������
	code_pointer cP;
	char i;
	while (1) {
		cP = locate_code_list(cL, code);//Ѱ��ȡ�����Ӧ��ַ
		if (cP == NULL) {//�����ڸ���Ʒ���������
			printf("�����ڸ�ȡ����,��y������ȡ��,n�˳�ȡ��");
			i = getchar();
			getchar();
			if (i == 'y') {
				return TRUE;//����trueΪ����ȡ��,falseΪ�˳�ȡ��
			}
			else if (i == 'n')
				return FALSE;//�˳�ȡ��
			else {
				printf("�������,Ĭ���˳�ȡ��\n");
				return FALSE;
			}
		}
		while (1) {		
			cP = locate_code_addr_list(cP->phonenum_p, code);
			if (cP == NULL) //�ڸ��������в����ڸ���Ʒ���������,��code_list���²���
				break;
			//������ʱ
			de_locker_list(cP->locker_p->head,cP->locker_p);//��ݹ�ȡ����Ʒ,������Դ
			cP->locker_p->head->state--;
			de_code_addr_list(cP->phonenum_p,cP->phonenum_p->sublist_prior);//ɾ���������¼
			cP->record_p->stuff.iftimeout = -1;//����״̬
			cP->record_p->code_p = NULL;//ȡ������
			if (cP->phonenum_p->sublist_head->next == NULL) {//���,�ú������п�ݾ�ȡ��
				de_phonenum_list(pL,cP->phonenum_p);//ɾ���ú���ڵ�
				de_code_list(cL,cP);//ɾ����ȡ����ڵ�
				printf("ȡ���ɹ�!\n");
				printf("��y������ȡ��,n�˳�ȡ��\n");
				i = getchar();
				getchar();
			//	printf("%d", (int)i);
				if (i == 'y')
				{
					return TRUE;
				}
				else if (i == 'n')
					return FALSE;//�˳�ȡ��
			}
			else//�ú��뻹�п��
			{
				de_code_list(cL, cP);//ɾ����ȡ����ڵ�
				printf("ȡ���ɹ�!\n");
				if (mode == 0) {//�ͻ�ģʽ
					printf("�û�%s:�����п��δȡ,��y������ȡ��,n�˳�ȡ��\n", cP->phonenum_p->phonenum);
				}
				else
					printf("��y������ȡ��,n�˳�ȡ��\n");
				i=getchar();
				getchar();
				//printf("%d", (int)i);
				if (i =='y')
				{
					if (mode == 1) //���Աģʽֱ������ȡ��
						return TRUE;
					printf("������ȡ����:");
					scanf("%s", code);
					getchar();
					continue;
				}
				else if (i == 'n')
					return FALSE;//�˳�ȡ��
			}
		}
		continue;
	}
	return OK;
}
Status put_stuff(code_list cL, deliverman_pointer dP, locker_list lL, phonenum_list pL, struct stuffs stuff,int size) {//Ͷ��
	code_pointer cP;
	phonenum_pointer pP;
	code_addr_pointer caP;
	cP = (code_pointer)malloc(sizeof(struct code_node));//�½�ȡ����ڵ�
	caP = (code_addr_pointer)malloc(sizeof(struct code_addr_node));//�����ڵ�
	char Scode[7];
	/*���ڸ�ڵĲ���*/
	if(insert_locker_list(lL)==ERROR)//�Զ�������,����(����)����ĸ�ڵ�ַ
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
	create_code(cL,Scode,size);
	strcpy(cP->code,Scode );//����ȡ���벢д��ȡ����ڵ�
	stuff.iftimeout = 0;//״̬��Ϊ���
	cP->stuff = stuff;
	cP->locker_p = lL->prior;//�������ĸ�ڵ�ַ
	cP->phonenum_p = pP;//����绰�ŵ�ַ
	cP->deliverman_p = dP;//������Ա��ַ
	/*����ȡ��������������*/
	caP->code_P = cP;
	/*�ڵ�������*/
	printf("%d�Ÿ���Ѵ�\n", cP->locker_p->num);
	insert_code_list(cL, cP);//����ȡ����
	insert_code_addr_list(pP,caP);//��������
	insert_record_list(dP,cP);//�����¼
	return OK;
}