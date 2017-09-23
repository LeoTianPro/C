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
void Ask();//ѯ�ʺ�����ѡ�����������ֱ���˳�ϵͳ

int main() { //������
	STU student[N];
	int i,n,m,studentNo;
	char s,M[10];
	STU tem;
	STU *p;
	while(1) {
		int id;
		printf("\t\t*****��ӭʹ��ѧ����Ϣ����ϵͳ*****\n");
		printf("\t\t**********************************\n");
		printf("\n\t�����빦�ܱ��\n");
		printf("\t1.���ļ��ж���%d��ѧ����Ϣ\n",N);
		printf("\t2.���ļ��������ȡ��n��(0<=n<=%d)ѧ������Ϣ\n",N-1);
		printf("\t3.����༶��ɼ���ʵ�ְ༶�ͳɼ����ۺϲ���\n");
		printf("\t4.�������ѧ��ĳ�ſγ̵���߷ֺͷ�����ߵ�ѧ��������\n");
		printf("\t5.������ѧ����ƽ���ɼ��ɵ͵��߽��м�ѡ������\n");
		printf("\t6.��ĳ���༶��ѧ����ƽ���ɼ��ɸߵ��ͽ�����������\n");
		printf("\t7.��ĳ��רҵ��ѧ����ĳ�ſγ̳ɼ��ɵ͵��߽���ֱ�Ӳ�������\n");
		printf("\t8.�����޸ĺõĵ�ѧ����Ϣ\n");
		printf("\t0..�˳�\n\n");
		scanf("%d",&id);
		switch(id) {
			case 1:
				Input(student,sizeof(student)/sizeof(STU));
				for(i=0; i<N; i++)
					Output(student+i);
				Ask();
				break;
			case 2:
				printf("������һ������(0<=n<=%d)��Enter����:",N-1);
				scanf("%d",&n);
				getchar();
				tem=Fetch(n);
				Output(&tem);
				Ask();
				break;
			case 3:
				printf("������༶:");
				scanf("%d",&n);
				getchar();
				printf("���������Ҫ��\'<\'��\'>\'��");
				scanf("%c",&s);
				printf("\n������������Ҫ��, �ܷ���:");
				scanf("%d",&m);
				Search(student,n,s,m);
				Ask();
				break;
			case 4:
				printf("������γ����(0&1&2):");
				scanf("%d",&n);
				studentNo=Max(student,n);
				printf("��%d����߷�Ϊ:%d\n",n,student[studentNo].score[n]);
				printf("����:%-10s\n",student[studentNo].name);
				Ask();
				break;
			case 5:
				Sort_select(student);
				printf("����ѧ����ƽ���ɼ��ɵ͵���������˳��Ϊ\n");
				for(i=0; i<N; i++)
					Output(student+i);
				Ask();
				break;
			case 6:
				printf("������༶���(1&2):");
				scanf("%d",&n);
				Sort_buble(student,n);
				Ask();
				break;
			case 7:
				printf("������רҵ����(computer,software,network):");
				scanf("%s",M);
				printf("������γ����(0&1&2):");
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

void Input(STU *p,int n) { //��������
	FILE *fp;
	int i;
	if((fp=fopen("studentInit.dat","rb"))==NULL) {
		printf("�ļ��򲻿�\n");
		exit(0);
	}
	for(i=0; i<n; i++)
		if(fread(p++,sizeof(STU),1,fp)!=1)
			printf("�ļ���ȡ����\n");
	fclose(fp);
}

void Output(STU *p) {
	printf("ѧ�ţ�%-10s������%-10s רҵ��%-10s�༶��%d �ɼ���%3d %3d %3d\n",p->num,p->name,p->major,p->classNo,p->score[0],p->score[1],p->score[2]);
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
		printf("�����뱣���ļ�����");
		gets(filename);
		if((fp=fopen(filename,"wb"))==NULL) {
			printf("�ļ��򲻿�\n");
			exit(0);
		}
		for(i=0; i<n; i++)
			if(fwrite(p++,sizeof(STU),1,fp)!=1)
				printf("�ļ���д����");
		fclose(fp);
	}

	void Ask() {
		int n;
		printf("\n������Ҫ�Ĺ�����ʵ�֣��Ƿ��������?\n\"1\" ���� ; \"2\" �˳�ϵͳ\n");
		scanf("%d",&n);
		if (n==2)
			exit(0);
	}

