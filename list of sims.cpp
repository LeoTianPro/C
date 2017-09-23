#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 12

struct Student {
	char num[15];
	char name[15];
	char major[10];
	int classNo;
	int score[3];
	struct Student *next;
};
typedef struct Student STU;

STU *CreateList(char *filename);
void Output(STU *head);
void OutOneNode(STU *p);
STU *Max(STU *head);
STU *Search_num(STU *head,char *num);
void InsertList(STU *head,STU stu);
void Delete_num(STU *head,char *num);
void Save(STU *head);
STU *Search_major_subject_score(STU *head, char *major, int subject, int grade);
void Delete_class_subject_score(STU *head, int classNo, int subject, int grade);

//������
int main() {
	int choose,subject,grade,classno;
	STU *h,*p,stu,*s;
	char filename[20],num[15],major[10];
	while(1) {
		printf("\t\t********��ӭʹ��ѧ����Ϣ����ϵͳ********\n");
		printf("\t\t****************************************\n");
		printf("\t\t1.���ļ��ж�ȡѧ������Ϣ\n");
		printf("\t\t2.���ȫ��ѧ����Ϣ\n");
		printf("\t\t3.���������ߵ�ѧ����Ϣ\n");
		printf("\t\t4.�������ĳ��ѧ�ŵ�ѧ������Ϣ\n");
		printf("\t\t5.��ѧ��˳�����һ����ѧ������Ϣ\n");
		printf("\t\t6.ɾ��ָ��ѧ�ŵ�ѧ�������ʣ�µ�ѧ������Ϣ\n");
		printf("\t\t7.����ĳרҵĳ�γ̵ĳɼ�С��ĳ������ѧ�������ѧ������Ϣ\n");
		printf("\t\t8.ɾ��ĳ�༶ĳ�γ̵ĳɼ�С��ĳ������ѧ�����������ѧ������Ϣ\n");
		printf("\t\t9.��ѧ����Ϣ�������ļ�\n");
		printf("\t\t****************************************\n\n");
		printf("��������Ҫִ�е��������\n");
		scanf("%d",&choose);
		switch(choose) {
			case 1: {
				h=CreateList(filename);
				printf("�ɹ���������\n");
				break;
			}
			case 2: {
				printf("����ѧ������Ϣ����:\n");
				Output(h);
				break;
			}
			case 3: {
				p=Max(h);
				printf("������ߵ�ѧ����ϢΪ��\n");
				OutOneNode(p);
				break;
			}
			case 4: {
				printf("��������ҵ�ѧ��ѧ�ţ�\n");
				scanf("%s",num);
				p=Search_num(h,num);
				printf("��ѧ����ϢΪ��\n");
				OutOneNode(p);
				break;
			}
			case 5: {
				printf("������Ҫ����ѧ����ѧ�ţ�\n");
				scanf("%s",stu.num);
				getchar();
				printf("������Ҫ����ѧ����������\n");
				scanf("%s",stu.name);
				getchar();
				printf("������Ҫ����ѧ����רҵ��\n");
				scanf("%s",stu.major);
				getchar();
				printf("������Ҫ����ѧ���İ༶��\n");
				scanf("%d",&stu.classNo);
				getchar();
				printf("������Ҫ����ѧ���ĵ�1�ųɼ���\n");
				scanf("%d",&stu.score[0]);
				getchar();
				printf("������Ҫ����ѧ���ĵ�2�ųɼ���\n");
				scanf("%d",&stu.score[1]);
				getchar();
				printf("������Ҫ����ѧ���ĵ�3�ųɼ���\n");
				scanf("%d",&stu.score[2]);
				getchar();
				InsertList(h,stu);
				printf("����������ѧ����ϢΪ��\n");
				Output(h);
				break;
			}
			case 6: {
				printf("��������ɾ����ѧ����ѧ�ţ�\n");
				scanf("%s",num);
				Delete_num(h,num);
				printf("ɾ���������ѧ����ϢΪ��\n");
				Output(h);
				break;
			}
			case 7: {
				printf("���������ѧ��רҵ��\n");
				scanf("%s",major);
				getchar();
				printf("���������ѧ���ڼ��ſγ̣���0,1,2��\n");
				scanf("%d",&subject);
				getchar();
				printf("������Ҫ��ﵽ�ķ�����\n");
				scanf("%d",&grade);
				getchar();
				s=Search_major_subject_score(h,major,subject,grade);
				Output(s);
				break;
			}
			case 8: {
				printf("���������ѧ���༶��\n");
				scanf("%d",&classno);
				getchar();
				printf("���������ѧ���ڼ��ſγ̣���0,1,2��\n");
				scanf("%d",&subject);
				getchar();
				printf("������Ҫ��ﵽ�ķ�����\n");
				scanf("%d",&grade);
				getchar();
				Delete_class_subject_score(h,classno,subject,grade);
				printf("ɾ���������ѧ����ϢΪ��\n\n");
				Output(h);
				break;
			}
			case 9: {
				Save(h);
				printf("����ɹ�\n");
				Output(h);
				break;
			}
			default:
				break;
				if((choose<1)||(choose>9))
					break;
		}
	}
}

//������������
//���ļ�����ʽ��ȡ����������
STU *CreateList(char *filename) {
	STU *head,*p,*s;
	FILE *fp;
	if((fp=fopen("studentInfo.dat","rb"))==NULL) {
		printf("error");
		exit(0);
	}
	head=(STU*)malloc(sizeof(STU)); 
	head->next=NULL;
	p=head;
	while(1) {
		s=(STU*)malloc(sizeof(STU));
		fread(s,sizeof(STU),1,fp);
		p->next=s;
		p=s;
		if(p->next==NULL)
			break;
	}
	fclose(fp);
	return head;
}

//������ѧ������Ϣ�������������������
void Output(STU *head) {
	STU *p;
	p=head->next;
	while(p!=NULL) {
		printf("ѧ��%s\t\t����%s\tרҵ%s\t�༶%d\t����%d\t��ѧ%d\tӢ��%d\t\n",p->num,p->name,p->major,p->classNo,p->score[0],p->score[1],p->score[2]);
		p=p->next;
	}
}

//�������е�һ��ָ���Ľ�����
void OutOneNode(STU *p) {
	if(p!=NULL)
		printf("ѧ��%s\t����%s\tרҵ%s\t�༶%d\t����%d\t��ѧ%d\tӢ��%d\t\n\n",p->num,p->name,p->major,p->classNo,p->score[0],p->score[1],p->score[2]);
}

//����ܳɼ�������ߵ�ѧ����Ϣ
STU *Max(STU *head) {
	STU *p,*s;
	int sum,max;
	p=head->next;
	max=(p->score[0]+p->score[1]+p->score[2]);//��ͷ�����һ���������ųɼ��ܺ͸�ֵ��max
	s=p;
	while(p!=NULL) {
		sum=(p->score[0]+p->score[1]+p->score[2]);
		if(max<sum) {
			max=sum;
			s=p;
		}//�Ƚϣ����max<sum,��ָ��s=p��
		else  p=p->next;//if��������ָ��p�����ƶ����������бȽ�
	}

	return s;//�������ֵ��ָ��
}

//����ָ��ѧ��ѧ������Ϣ
STU *Search_num(STU *head,char *num) {
	STU *p;
	p=head->next;
	while(p!=NULL) {
		if(strcmp(num,p->num)==0)
			return p;
		else p=p->next;
	}
}

//������������һ����ѧ������Ϣ������ѧ��˳�򲻱�
void InsertList(STU *head,STU stu) {
	STU *p,*pnew;
	pnew=(STU*)malloc(sizeof(STU));
	p=head->next;
//����ѧ������Ϣ���ݸ�ָ��p�е�һ���ṹ�������
	strcpy(pnew->num,stu.num);
	strcpy(pnew->name,stu.name);
	strcpy(pnew->major,stu.major);
	pnew->classNo=stu.classNo;
	pnew->score[0]=stu.score[0];
	pnew->score[1]=stu.score[1];
	pnew->score[2]=stu.score[2];


	while(p->next!=NULL) {
		if(strcmp(pnew->num,p->next->num)<0) {
			pnew->next=p->next;//�������뵽����ָ��λ����
			p->next=pnew;
			break;
		} else p=p->next; //if����������������ѧ��֮��ıȽ�
	}

	if(p->next==NULL)//p->next�����һ����㣬��ôpnew�Ͳ������ĺ���
		p->next=pnew;
}

//ɾ��ĳѧ��ѧ����Ϣ�����ɾ���������ѧ����Ϣ
void Delete_num(STU *head,char *num) {
	STU *p,*s;
	s=head;//ָ��һ���ս��
	p=head->next;
	while(p!=NULL) {
		if(strcmp(num,p->num)==0) {
			s->next=p->next;//������p��λ�ø�p->next��
			free(p);//ɾ��p
			p=p->next;
			break;
		} else s=p; //if����������s�Ƶ�p��λ�á�
		p=p->next;//p�Ƶ�p->next��λ��.
	}
}

//����ĳרҵĳ�γ̵ĳɼ�С��ĳ������ѧ�������ѧ������Ϣ
STU *Search_major_subject_score(STU *head, char *major, int subject , int grade ) {
	int n=0;
	STU *h,*p,*s;
	h=(STU*)malloc(sizeof(STU));
	h->next=NULL;
	p=h;
	while(head!=NULL) {
		if(strcmp(head->major,major)==0)
			if(head->score[subject]<grade) {
				s=(STU*)malloc(sizeof(STU));
				*s=*head;
				s->next=NULL;
				if(n==0) {
					*h=*s;
					n++;
				} else {
					p->next=s;
					p=p->next;
				}
			}
		head=head->next;
	}
	return h;
}

//ɾ��ĳ���༶ĳ�ſγ̷���С��ĳ��ֵ��ѧ����Ϣ�����ɾ�����ѧ����Ϣ
void Delete_class_subject_score(STU *head,int classno,int subject,int grade) {
	STU *p;
	char M[10];
	p=head->next;
	while(p!=NULL) {
		if(p->classNo==classno&&p->score[subject]<grade) {
			strcpy(M,p->num);
			p=p->next;
			Delete_num(head,M);
		} else  p=p->next;
	}
}

//�����µ�ѧ����Ϣ�����µ��ļ���
void Save(STU *head) {
	int i;
	FILE *fp;
	STU *p=head->next;
	if((fp=fopen("studentInfoNew","wb"))==NULL) {
		printf("error\n");
		return;
	}
	for(i=0; i<N; i++) {
		if(fwrite(p++,sizeof(STU),1,fp)!=1)
			printf("error\n");
	}
	fclose(fp);
}
