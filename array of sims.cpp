#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 10

struct Student {
	char num[15];
	char name[15];
	char major[10];
	int classNo;
	int score[3];
};
typedef struct Student STU;

void Input(STU *p,int n);
void Save(STU *p,int n);
void Output(STU *p);
STU Fetch(int studentNo);
int Max(STU *p,int classNo);
void Sort_select(STU *p);
void Sort_buble(STU *p,int n);
void Sort_insert(STU *p,int n,char M[]);
void Search(STU *p,int classNo,char s,int scoreSum);
void Ask();//询问函数，选择继续操作或直接退出系统

int main() { //主函数
	STU student[N];
	int i,n,m,studentNo;
	char s,M[10];
	STU tem;
	STU *p;
	while(1) {
		int id;
		printf("\t\t*****欢迎使用学生信息管理系统*****\n");
		printf("\t\t**********************************\n");
		printf("\n\t请输入功能编号\n");
		printf("\t1.从文件中读入%d个学生信息\n",N);
		printf("\t2.从文件中随机读取第n个(0<=n<=%d)学生的信息\n",N-1);
		printf("\t3.输入班级与成绩，实现班级和成绩的综合查找\n");
		printf("\t4.输出所有学生某门课程的最高分和分数最高的学生的姓名\n");
		printf("\t5.对所有学生按平均成绩由低到高进行简单选择排序\n");
		printf("\t6.对某个班级的学生按平均成绩由高到低进行起泡排序\n");
		printf("\t7.对某个专业的学生按某门课程成绩由低到高进行直接插入排序\n");
		printf("\t8.保存修改好的的学生信息\n");
		printf("\t0..退出\n\n");
		scanf("%d",&id);
		switch(id) {
			case 1:
				Input(student,sizeof(student)/sizeof(STU));
				for(i=0; i<N; i++)
					Output(student+i);
				Ask();
				break;
			case 2:
				printf("请输入一个整数(0<=n<=%d)，Enter结束:",N-1);
				scanf("%d",&n);
				getchar();
				tem=Fetch(n);
				Output(&tem);
				Ask();
				break;
			case 3:
				printf("请输入班级:");
				scanf("%d",&n);
				getchar();
				printf("请输入查找要求：\'<\'或\'>\'：");
				scanf("%c",&s);
				printf("\n请继续输入查找要求, 总分数:");
				scanf("%d",&m);
				Search(student,n,s,m);
				Ask();
				break;
			case 4:
				printf("请输入课程序号(0&1&2):");
				scanf("%d",&n);
				studentNo=Max(student,n);
				printf("第%d科最高分为:%d\n",n,student[studentNo].score[n]);
				printf("姓名:%-10s\n",student[studentNo].name);
				Ask();
				break;
			case 5:
				Sort_select(student);
				printf("所有学生按平均成绩由低到高排序后的顺序为\n");
				for(i=0; i<N; i++)
					Output(student+i);
				Ask();
				break;
			case 6:
				printf("请输入班级序号(1&2):");
				scanf("%d",&n);
				Sort_buble(student,n);
				Ask();
				break;
			case 7:
				printf("请输入专业名称(computer,software,network):");
				scanf("%s",M);
				printf("请输入课程序号(0&1&2):");
				scanf("%d",&n);
				Sort_insert(student,n,M);
				Ask();
				break;
			case 8:
				getchar();
				Save(student,sizeof(STU));
				Ask();
				break;
			default:
				printf("error");
				break;
		}
		if((id<1)||(id>8))   break;
	}
}

void Input(STU *p,int n) { //被调函数
	FILE *fp;
	int i;
	if((fp=fopen("studentInit.dat","rb"))==NULL) {
		printf("文件打不开\n");
		exit(0);
	}
	for(i=0; i<n; i++)
		if(fread(p++,sizeof(STU),1,fp)!=1)
			printf("文件读取错误\n");
	fclose(fp);
}

void Output(STU *p) {
	printf("学号：%-10s姓名：%-10s 专业：%-10s班级：%d 成绩：%3d %3d %3d\n",p->num,p->name,p->major,p->classNo,p->score[0],p->score[1],p->score[2]);
}

STU Fetch(int studentNo) {
	STU  tem;
	FILE *fp;
	fp=fopen("studentInit.dat","rb");
	fseek(fp,(long)(studentNo*sizeof(STU)),0);
	fread(&tem,sizeof(STU),1,fp);
	fclose(fp);
	return tem;
}

void Search(STU *p,int classNo,char s,int scoreSum) {
	int sum;
	for(int i=0; i<N; i++,p++) {
		if(p->classNo==classNo) {
			sum=p->score[0]+p->score[1]+p->score[2];
			if(s=='>')
				if(sum>scoreSum)
					Output(p);
				else;
			else if(sum<scoreSum)
				Output(p);
		}
	}


}

int Max(STU *p,int scoreIndex) {
	int i,k=0;
	for(i=1; i<N; i++)
		if((p+k)->score[scoreIndex]<(p+i)->score[scoreIndex])
			k=i;
	return k;
}

void Sort_select(STU *p) {
	int i,k,t;
	float a[N];
	STU T;
	for(i=0; i<N-1; i++) {
		a[i]=((p+i)->score[0]+(p+i)->score[1]+(p+i)->score[2])/3.0;
		for(k=i+1; k<N; k++) {
			a[k]=((p+k)->score[0]+(p+k)->score[1]+(p+k)->score[2])/3.0;
			if(a[i]>a[k]) {
				t=a[k];
				a[k]=a[i];
				a[i]=t;
				T=*(p+i);
				*(p+i)=*(p+k);
				*(p+k)=T;
			}
		}
	}
}

void Sort_buble(STU *p,int n) {
	STU stu_class_ave[N];
	int i,j,t,count=0;
	float a[N];
	STU T;
	for(i=0; i<N; i++)
		if((p+i)->classNo==n) {
			stu_class_ave[count]=*(p+i);
			count++;
		}
	for(i=0; i<count; i++)
		a[i]=(stu_class_ave[i].score[0]+stu_class_ave[i].score[1]+stu_class_ave[i].score[2])/3.0;
	for(i=0; i<count; i++)
		for(j=0; j<count-i; j++)
			if(a[j]<a[j+1]) {
				t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
				T=stu_class_ave[j];
				stu_class_ave[j]=stu_class_ave[j+1];
				stu_class_ave[j+1]=T;
			}
	for(i=0; i<count; i++)
		Output(&stu_class_ave[i]);
}

void Sort_insert(STU *p,int n,char M[])

{
	STU stu_class_subject[N];
	int i,j,count=1;
	for(i=0; i<N; i++)
		if(strcmp((p+i)->major,M)==0)
			stu_class_subject[count++]=*(p+i);
	for(i=2; i<count; i++) {
		stu_class_subject[0]=stu_class_subject[i];
		for(i=2; i<count; i++) {
			stu_class_subject[0]=stu_class_subject[i];
			for(j=i-1; stu_class_subject[0].score[n]<stu_class_subject[j].score[n]; j--)
				stu_class_subject[j+1]=stu_class_subject[j];
			stu_class_subject[j+1]=stu_class_subject[0];
		}
		for(i=1; i<count; i++)
			Output(&stu_class_subject[i]);

	}

	void Save(STU *p,int n) {
		FILE *fp;
		char filename[20];
		int i;
		printf("请输入保存文件名：");
		gets(filename);
		if((fp=fopen(filename,"wb"))==NULL) {
			printf("文件打不开\n");
			exit(0);
		}
		for(i=0; i<n; i++)
			if(fwrite(p++,sizeof(STU),1,fp)!=1)
				printf("文件书写错误");
		fclose(fp);
	}

	void Ask() {
		int n;
		printf("\n您所需要的功能已实现，是否继续进行?\n\"1\" 继续 ; \"2\" 退出系统\n");
		scanf("%d",&n);
		if (n==2)
			exit(0);
	}

