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

//主函数
int main() {
	int choose,subject,grade,classno;
	STU *h,*p,stu,*s;
	char filename[20],num[15],major[10];
	while(1) {
		printf("\t\t********欢迎使用学生信息管理系统********\n");
		printf("\t\t****************************************\n");
		printf("\t\t1.从文件中读取学生的信息\n");
		printf("\t\t2.输出全部学生信息\n");
		printf("\t\t3.输出分数最高的学生信息\n");
		printf("\t\t4.具体查找某个学号的学生的信息\n");
		printf("\t\t5.按学号顺序插入一个新学生的信息\n");
		printf("\t\t6.删除指定学号的学生，输出剩下的学生的信息\n");
		printf("\t\t7.查找某专业某课程的成绩小于某分数的学生，输出学生的信息\n");
		printf("\t\t8.删除某班级某课程的成绩小于某分数的学生，输出其他学生的信息\n");
		printf("\t\t9.将学生信息存入新文件\n");
		printf("\t\t****************************************\n\n");
		printf("输入您想要执行的命令序号\n");
		scanf("%d",&choose);
		switch(choose) {
			case 1: {
				h=CreateList(filename);
				printf("成功建立链表\n");
				break;
			}
			case 2: {
				printf("所有学生的信息如下:\n");
				Output(h);
				break;
			}
			case 3: {
				p=Max(h);
				printf("分数最高的学生信息为：\n");
				OutOneNode(p);
				break;
			}
			case 4: {
				printf("请输入查找的学生学号：\n");
				scanf("%s",num);
				p=Search_num(h,num);
				printf("该学生信息为：\n");
				OutOneNode(p);
				break;
			}
			case 5: {
				printf("请输入要插入学生的学号：\n");
				scanf("%s",stu.num);
				getchar();
				printf("请输入要插入学生的姓名：\n");
				scanf("%s",stu.name);
				getchar();
				printf("请输入要插入学生的专业：\n");
				scanf("%s",stu.major);
				getchar();
				printf("请输入要插入学生的班级：\n");
				scanf("%d",&stu.classNo);
				getchar();
				printf("请输入要插入学生的第1门成绩：\n");
				scanf("%d",&stu.score[0]);
				getchar();
				printf("请输入要插入学生的第2门成绩：\n");
				scanf("%d",&stu.score[1]);
				getchar();
				printf("请输入要插入学生的第3门成绩：\n");
				scanf("%d",&stu.score[2]);
				getchar();
				InsertList(h,stu);
				printf("插入后的所有学生信息为：\n");
				Output(h);
				break;
			}
			case 6: {
				printf("输入你想删除的学生的学号：\n");
				scanf("%s",num);
				Delete_num(h,num);
				printf("删除后的所有学生信息为：\n");
				Output(h);
				break;
			}
			case 7: {
				printf("请输入查找学生专业：\n");
				scanf("%s",major);
				getchar();
				printf("请输入查找学生第几门课程：（0,1,2）\n");
				scanf("%d",&subject);
				getchar();
				printf("请输入要求达到的分数：\n");
				scanf("%d",&grade);
				getchar();
				s=Search_major_subject_score(h,major,subject,grade);
				Output(s);
				break;
			}
			case 8: {
				printf("请输入查找学生班级：\n");
				scanf("%d",&classno);
				getchar();
				printf("请输入查找学生第几门课程：（0,1,2）\n");
				scanf("%d",&subject);
				getchar();
				printf("请输入要求达到的分数：\n");
				scanf("%d",&grade);
				getchar();
				Delete_class_subject_score(h,classno,subject,grade);
				printf("删除后的所有学生信息为：\n\n");
				Output(h);
				break;
			}
			case 9: {
				Save(h);
				printf("保存成功\n");
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

//被调函数部分
//以文件的形式读取，建立链表
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

//将所有学生的信息按照链表的排序进行输出
void Output(STU *head) {
	STU *p;
	p=head->next;
	while(p!=NULL) {
		printf("学号%s\t\t姓名%s\t专业%s\t班级%d\t语文%d\t数学%d\t英语%d\t\n",p->num,p->name,p->major,p->classNo,p->score[0],p->score[1],p->score[2]);
		p=p->next;
	}
}

//将链表中的一个指定的结点输出
void OutOneNode(STU *p) {
	if(p!=NULL)
		printf("学号%s\t姓名%s\t专业%s\t班级%d\t语文%d\t数学%d\t英语%d\t\n\n",p->num,p->name,p->major,p->classNo,p->score[0],p->score[1],p->score[2]);
}

//输出总成绩分数最高的学生信息
STU *Max(STU *head) {
	STU *p,*s;
	int sum,max;
	p=head->next;
	max=(p->score[0]+p->score[1]+p->score[2]);//将头结点后的一个结点的三门成绩总和赋值给max
	s=p;
	while(p!=NULL) {
		sum=(p->score[0]+p->score[1]+p->score[2]);
		if(max<sum) {
			max=sum;
			s=p;
		}//比较，如果max<sum,让指针s=p；
		else  p=p->next;//if不成立，指针p向下移动，继续进行比较
	}

	return s;//返回最大值的指针
}

//查找指定学号学生的信息
STU *Search_num(STU *head,char *num) {
	STU *p;
	p=head->next;
	while(p!=NULL) {
		if(strcmp(num,p->num)==0)
			return p;
		else p=p->next;
	}
}

//向链表中输入一个新学生的信息，保持学号顺序不变
void InsertList(STU *head,STU stu) {
	STU *p,*pnew;
	pnew=(STU*)malloc(sizeof(STU));
	p=head->next;
//将新学生的信息传递给指针p中的一个结构体变量。
	strcpy(pnew->num,stu.num);
	strcpy(pnew->name,stu.name);
	strcpy(pnew->major,stu.major);
	pnew->classNo=stu.classNo;
	pnew->score[0]=stu.score[0];
	pnew->score[1]=stu.score[1];
	pnew->score[2]=stu.score[2];


	while(p->next!=NULL) {
		if(strcmp(pnew->num,p->next->num)<0) {
			pnew->next=p->next;//将结点插入到链表指定位置中
			p->next=pnew;
			break;
		} else p=p->next; //if不成立，继续进行学号之间的比较
	}

	if(p->next==NULL)//p->next是最后一个结点，那么pnew就插在它的后面
		p->next=pnew;
}

//删除某学号学生信息，输出删除后的所有学生信息
void Delete_num(STU *head,char *num) {
	STU *p,*s;
	s=head;//指向一个空结点
	p=head->next;
	while(p!=NULL) {
		if(strcmp(num,p->num)==0) {
			s->next=p->next;//将本来p的位置给p->next。
			free(p);//删除p
			p=p->next;
			break;
		} else s=p; //if不成立，将s移到p的位置。
		p=p->next;//p移到p->next的位置.
	}
}

//查找某专业某课程的成绩小于某分数的学生，输出学生的信息
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

//删除某个班级某门课程分数小于某个值的学生信息，输出删除后的学生信息
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

//将更新的学生信息存入新的文件中
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
