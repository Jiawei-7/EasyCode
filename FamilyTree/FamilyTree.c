#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct infor
{

	char name[100];//名字 
	int sex;//性别 
	char fed[100];//配偶姓名 
	int seniority;
	int birth;//生日
	char fatherName[100];//父亲

}infor;

typedef struct CSTNode
{
	infor data;
	struct CSTNode *firstChild, *nextSibling, *father;
}CSTNode, *CSTree, *CSForest;


//用于层次遍历 
typedef struct LNode{               //链表和链表结点类型 
	CSTree data;                     //数据域
	struct LNode *next;             //指针域
}LNode, *LinkList;



typedef enum status{
	TRUE=1,
	FALSE=-1,
	OK=2,
	ERROR=-2,
	SUCCESS=1,
	OVERFLOW=-1,
	EMPTY=0
}Status;//枚举类型返回值




void menu();//已经有族谱的菜单 
void menu2();//还没有族谱的，需要构建的菜单 
void init();//初始化，将文件写入 
void initCSTNode(CSTree*A);//初始化节点，将指针置空 
int  isEmpty();//判断文件内容是否为空，为空则为菜单2 
int Createfamilytree();//创建一个族谱，则是设立一个祖先 
void createCSTNode(CSTree*A);//创建一个节点，需要调用初始化函数 
void Insert();//插入功能的服务函数，用于接收用户输入 
void insertNode(CSTree*father, CSTree*child);//插入函数的应用函数，用于连接节点 
void Del();//删除功能的服务函数 
void deleteNode(CSTree *A);//删除函数的应用函数，主要用于将删除节点的父亲节点与兄弟节点的连接 
void Modify();//修改功能的服务函数，接收要删除谁 
void changeFather(CSTree *A, CSForest T);
void changeBirth(CSTree *A);
void changeMsg(CSTree*B, CSForest T);//通过查询函数后 
void Search();//查询功能的服务，用于接收名字 
void searchNode(CSForest T, char name[100], CSTree*B);//查询功能的应用函数，用于遍历 
void showMsg(CSTree *B);//展示函数，用于输出个人信息 
void SearchRel();//查询两个关系 
void PrintAsTree(CSTree T);//凹入表输出族谱 
void destroy(CSTree*A);//销毁以A为根节点的树 
void inorderCousin(CSTree T, CSTree A);//输出所有的堂兄弟 
void refreshSeniority(CSForest*T);//更新辈分
Status PrintTree(CSTree t);
Status Traverse(CSTree T, LinkList L);
void relationship();//判断，想找什么关系的人 
Status InitQueue(LinkList *L);//初始队列 
LNode* CreateNode(CSTNode *p);//创建队列节点 
Status Enqueue(LNode *p, CSTNode *q);//入队 
Status Dequeue(LNode *p, CSTree *q);//出队 
Status IfEmpty(LinkList L);//判空 
void DestroyQueue(LinkList L);//销毁队列 
void save();

struct infor per[100];
CSTree  anc;
CSTNode *A;
CSTNode *B;
char fatherName[100];


int main()
{
	//printf("main");
	char fatherName[100];
	int judge = 3;
	judge = isEmpty();
	    //printf("%d",judge);
	if (judge){
		init();
	}


	int e = 0, f = 0;
	if (judge == 0)
	{
		menu2();
		int a;
		scanf("%d", &a);
		switch (a)
		{
		case 1: Createfamilytree();
			judge = 1;
			break;
		case 2: return 0;
			break;
		}
	}

	while (e == 0)
	{

		if (judge == 1)
		{

			menu();
			int a;
			scanf("%d", &a);
			switch (a)
			{
			case 1: Insert();
				break;
			case 2: Del();
				break;
			case 3:Modify();
				break;
			case 4: Search();
				break;
			case 5:SearchRel();
				break;
			case 6: relationship();
				break;
			case 7: PrintAsTree(anc);
				break;
			case 8: PrintTree(anc);
				break;
			case 9:save();
				return 0;
				break;
			}
		}
	}




}

void menu2()
{
	printf("\n\n\t\t\t\t\t\t族谱管理系统");
	printf("\n\n");
	printf("\n\t\t\t\t\t1.构建族谱");
	printf("\n\t\t\t\t\t2.结束该系统");
	printf("\n\t\t\t\t\t请输入您要的操作所对应的数字：");
	printf("");
}

void menu()
{
	printf("\n\n\t\t\t\t\t\t族谱管理系统");
	printf("\n\n");
	printf("\n\t\t\t\t\t1.添加人物");
	printf("\n\t\t\t\t\t2.删除人物");
	printf("\n\t\t\t\t\t3.修改人物信息");
	printf("\n\t\t\t\t\t4.查找人物信息");
	printf("\n\t\t\t\t\t5.判断两人关系");
	printf("\n\t\t\t\t\t6.人物关系查询");
	printf("\n\t\t\t\t\t7.凹入表打印家谱");
	printf("\n\t\t\t\t\t8.层次遍历族谱");
	printf("\n\t\t\t\t\t9.结束该系统并保存");
	printf("\n\t\t\t\t\t请输入您要的操作所对应的数字：");
	printf("");
}

int  isEmpty()
{
	int sta = 0;
	//    printf("进入判空"); 
	FILE*r;
	r = fopen("familytree.txt", "r");
	if (r == NULL)
	{
		printf("打开文件失败!!!!!");
	}

	char fatherName[100];
	createCSTNode(&A);
	fread(&(A->data), sizeof(struct infor), 1, r);
	//    fscanf(r,"%s%d%s%d%d%s",&A->data.name,&A->data.sex,&A->data.fed,&A->data.seniority,&A->data.birth,&A->data.fatherName);
	//    printf("\n%s",A->data.fatherName);
	//    printf("\n%s",A->data.name); 
	//    printf("\n%s",A->data.fed);
	//    printf("\n%d",A->data.sex);
	//    printf("\n%d",A->data.birth);

	if (A->data.birth == 0)
	{
		printf("\n\t\t\t\t\t\t族谱尚未搭建");
		free(A);
		A = NULL;
		fclose(r);
		return sta;
	}
	sta = 1;
	A = NULL;
	fclose(r);
	return sta;
}

void save(){

	FILE *fp;
	if ((fp = fopen("familytree.txt", "w")) == NULL)
	{
		printf("家谱文件不存在！\n");		return;
	}



	LinkList L;
	if (anc == NULL){
		printf(" 族谱不存在\n");
	}

	InitQueue(&L);//初始化队列 

	CSTree P = anc;
	CSTree K;
	int i = 0;
	int j = 1;
	while (P)//p指向森林里的每棵树
	{
		//        printf("第%d个家族\n",j);
		K = P;//利用k来遍历以p为根节点子树中的节点
		Enqueue(L, K);//根节点入队
		while (IfEmpty(L) == FALSE)//只要队列不为空就依次出队直到队空
		{
			Dequeue(L, &K);
			if (i != K->data.seniority){
				printf("\n");
				i = K->data.seniority;
			}
			printf("[%d|%d|%s]", K->data.seniority, K->data.birth, K->data.name);


			fwrite(&(K->data), sizeof(infor), 1, fp);
			//            fwrite(&(K->data.sex),sizeof(int),1,fp);    
			//            fwrite(&(K->data.fed),100*sizeof(char),1,fp);
			//            fwrite(&(K->data.seniority),sizeof(int),1,fp);
			//            fwrite(&(K->data.birth),sizeof(int),1,fp);
			//            fwrite(&(K->data.fatherName),100*sizeof(char),1,fp);


			if (K->firstChild){//如果该节点不是森林中的叶节点，则进入下一层
				K = K->firstChild;
				Enqueue(L, K);
				while (K->nextSibling)
				{//入队同层兄弟节点
					K = K->nextSibling;
					Enqueue(L, K);
				}
			}
		}
		P = P->nextSibling;
		printf("\n");
		j++;
	}


	DestroyQueue(L);//销毁队列 	
	fclose(fp);

}

void init(){//初始化，写入文件中的家谱 

	printf("开始初始化族谱");


	CSTree T;
	createCSTNode(&T);
	FILE*r;
	r = fopen("familytree.txt", "r");
	if (r == NULL)
	{
		printf("打开文件失败!");
	}

	if (fread(&(T->data), sizeof(struct infor), 1, r)) {
	}
	anc = T;
	char fatherName[100];
	createCSTNode(&A);
	createCSTNode(&B);
	while (fread(&(A->data), sizeof(struct infor), 1, r))
	{

		printf("\n%s %d %s %d %s", A->data.name, A->data.sex, A->data.fed, A->data.birth, A->data.fatherName);
		searchNode(anc, A->data.fatherName, &B);
		printf("\n%s %d %s %d %s", B->data.name, B->data.sex, B->data.fed, B->data.birth, B->data.fatherName);
		if (B->data.birth == 0){
			printf("此人的父亲不在家谱里！\n");
			free(A);
		}
		if (B->data.seniority != 0 && B->data.birth >= A->data.birth){
			printf("生日不能比父亲早\n");
			free(A);
		}
		else {
			insertNode(&B, &A);
			A = NULL;
			createCSTNode(&A);
		}

	}

	fclose(r);
}








void createCSTNode(CSTree*A){//创建一个节点 
	// printf("创节点"); 
	(*A) = (CSTree)malloc(sizeof(CSTNode));
	if ((*A) == NULL)return;
	initCSTNode(&(*A));
}


void initCSTNode(CSTree*A){// 进行初始化，避免指针乱指 
	if ((*A) == NULL)return;
	(*A)->father = NULL;
	(*A)->firstChild = NULL;
	(*A)->nextSibling = NULL;
	(*A)->data.birth = 0;
	(*A)->data.seniority = 0;
	(*A)->data.sex = 0;
	strcpy((*A)->data.name, "NULL");//名字 
	strcpy((*A)->data.fed, "无");//配偶名字 
	strcpy((*A)->data.fatherName, "NULL");//父亲名字 
	return;
}




int Createfamilytree()          //创建族谱树函数，即为空家谱添加一个祖先
{
	int i, j = 1;
	CSTree *A = (CSTree*)malloc(sizeof(CSTNode));;
	createCSTNode(A);
	printf("开始录入祖先");
	printf("请输入此人名字:\n");
	scanf("%s", (*A)->data.name);

	printf("请输入此人性别(男输入1，女输入0):\n");
	while (j)
	{
		scanf("%d", &((*A)->data.sex));
		switch ((*A)->data.sex)
		{
		case 1:
			j = 0;
			break;
		case 0:
			j = 0;
			break;
		default:
			printf("输入数据有误,请重新输入!\n");
			break;
		}
	}


	printf("配偶为：（若无则填无）\n");

	scanf("%s", &((*A)->data.fed));


	printf("请输入此人生日:\n");
	scanf("%d", &(*A)->data.birth);

	(*A)->data.seniority = 0;
	anc = *A;
	return 1;
}


void Insert(){
	CSForest T = anc;
	char fatherName[100];


	createCSTNode(&A);//自己信息 
	createCSTNode(&B); //父亲信息
	printf("\n\t\t请输入：姓名    性别(1/0)   配偶姓名    生日       父亲姓名\n ");
	printf(" \t\t例如： 大头儿子  1           无        2003       小头爸爸\n ");
	printf("\n\t\t\n不同输入之间隔一个空格");
	scanf("%s %d %s %d %s", &A->data.name, &A->data.sex, &A->data.fed, &A->data.birth, &A->data.fatherName);
	printf("%s %d %s %d %s", A->data.name, A->data.sex, A->data.fed, A->data.birth, &A->data.fatherName);
	printf("%s", A->data.fatherName);
	if (A->data.sex != 1 && A->data.sex != 0){
		printf("性别输入有误！\n");
		free(A);
		A = NULL;
		return;

	}

	searchNode(T, A->data.fatherName, &B);//获取父节点 
	if (B == NULL){
		printf("此人的父亲不在家谱里！\n");
		free(A);
		A = NULL;
		return;
	}
	if (B != NULL){
		printf("\n输出该人父亲\n");
		showMsg(&B);
	}
	if (B->data.seniority != 0 && B->data.birth >= A->data.birth){
		printf("生日不能比父亲早\n");
		free(A);
		A = NULL;
		B = NULL;
		return;
	}
	insertNode(&B, &A);
	return;
}



void insertNode(CSTree*father, CSTree*child){
	(*child)->data.seniority = (*father)->data.seniority + 1;
	(*child)->father = (*father);
	int birth = (*child)->data.birth;
	CSTree bro1 = (*father)->firstChild;
	if (bro1 == NULL){
		(*father)->firstChild = (*child);//没有孩子，直接插入到firstChild中 
		return;
	}
	if (bro1->data.birth >= birth){//有孩子，且年纪比需插入的年纪小(因为想要父亲的firstchild为长子) 
		(*child)->nextSibling = bro1;
		(*father)->firstChild = (*child);
		return;
	}
	//以下为有孩子，但孩子年纪比需要插入的年纪大 ，重新遍历 
	CSTree bro2 = (*father)->firstChild;
	bro1 = bro2->nextSibling;//此时bro1指向第二个孩子 
	for (; bro1 != NULL&&birth>bro1->data.birth;){//进行遍历，找到那个年纪小于需插入的孩子 bro1 
		bro2 = bro2->nextSibling;
		bro1 = bro2->nextSibling;
	}
	(*child)->nextSibling = bro1;
	bro2->nextSibling = (*child);
	printf("插入成功");
	refreshSeniority(&anc);//更新辈分
	return;
}

void refreshSeniority(CSForest*T){
	if (NULL == (*T))return;
	if ((*T)->father == NULL)
		(*T)->data.seniority = 0;
	else{
		(*T)->data.seniority = (*T)->father->data.seniority + 1;
	}
	refreshSeniority(&((*T)->firstChild));
	refreshSeniority(&((*T)->nextSibling));
	return;
}


void Del(){//删除服务函数 
	A = NULL;
	//    createCSTNode(&A);
	char name[100];
	printf("请输入姓名:");
	scanf("%s", name);
	searchNode(anc, name, &A);
	if (A == NULL){
		printf("不存在名为%s的人\n", name);
		return;
	}
	deleteNode(&A);
	A = NULL;
}


void deleteNode(CSTree *A){
	CSTree bro1;
	if ((*A)->father->firstChild == (*A)){//假如父亲的firstchild为他，则需要找替换 
		(*A)->father->firstChild = (*A)->nextSibling;
	}
	else
	{
		for (bro1 = (*A)->father->firstChild; bro1->nextSibling != (*A);){//如果不是，则需要找到他的前一个 
			bro1 = bro1->nextSibling;
		}
		bro1->nextSibling = (*A)->nextSibling;//将被删除节点的前一个与后一个相连 
	}
	(*A)->nextSibling = NULL;
	(*A)->father = NULL;
	system("pause");
	destroy(&(*A));
}


void destroy(CSTree*A){//销毁以A节点为祖先的树 
	if ((*A) == NULL)return;
	destroy(&((*A)->firstChild));
	destroy(&((*A)->nextSibling));
	free(*A);
}


void Search(){

	A = NULL;
	char a[100];
	printf("请输入你需要查找的人物名字");
	scanf("%s", &a);
	searchNode(anc, a, &A);
	if (A != NULL){
		printf("找到该人");
		showMsg(&A);
		return;
	}
	printf("找不到该人");
	return;
}


void searchNode(CSForest T, char name[100], CSTree*B){
	if (T == NULL)  {
		//	printf("\n祖先为空");
		return;
	}
	//    printf("\n祖先不为空"); 
	if (strcmp(T->data.name, name) == 0){
		(*B) = T;
		printf("\n找到匹配");
		//         return;
	}
	searchNode(T->firstChild, name, &(*B));
	//    if((*B)->data.birth!=0) {
	//    return;	
	//	}
	searchNode(T->nextSibling, name, &(*B));
	return;
}


void showMsg(CSTree *B){

	printf("姓名： ");
	printf("%s", (*B)->data.name);
	printf("\n性别：");
	if ((*B)->data.sex){
		printf("男  ");
	}
	else{
		printf("女  ");
	}
	printf("配偶： ");
	printf("%s", (*B)->data.fed);
	printf("生日： ");
	printf("%d", (*B)->data.birth);
	printf("父亲姓名：");
	printf("%s", (*B)->data.fatherName);
}




void Modify(){//改函数的服务函数


	A = NULL;
	char name[100];
	printf("请输入姓名:");
	scanf("%s", name);
	searchNode(anc, name, &A);
	if (A == NULL){
		printf("不存在名为%s的人\n", name);
		return;
	}
	if (A != NULL){
		printf("\n找到该人");
	}
	changeMsg(&A, anc);
	printf("\n修改成功");
	showMsg(&A);
	A = NULL;
}


void changeMsg(CSTree*B, CSForest T){//改函数的服务函数 
	if ((*B) == NULL)return;
	if ((*B)->data.seniority == 0){
		printf("该节点为森林根结点，禁止操作！\n");
		system("pause"); return;
	}
	int choice;
	//    A:system("cls");
	showMsg(&(*B));
	printf("\n");
	printf("你想改变什么\n");
	printf("\n");
	printf("********************************\n");
	printf("\n");
	printf("    1.name 姓名        2.sex性别\n");
	printf("\n");
	printf("    3.fedname配偶      4.birth生日\n");
	printf("\n");
	printf("    5.father父亲     6.break退出\n  ");
	printf("\n");
	printf("    ");
	printf("\n");
	printf("********************************\n");
	printf("\n");
	printf("请输入序号：\n");
	fflush(stdin);
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("请输入新名字:");
		char name[100];
		scanf("%s", name);
		strcpy((*B)->data.name, name);
		break;
		//            system("pause");
	case 2:
		printf("你的性别为:（男性请输入1，女性请输入2）");
		int sex;
		fflush(stdin);
		scanf("%d", &sex);
		if (sex != 0 || sex != 1){
			printf("输入有误\n");
			//                system("pause"); 
		}
		(*B)->data.sex = sex;
		//            system("pause"); 
		break;
	case 3:
		printf("请输入配偶名字:");
		char fed[100];
		fflush(stdin);
		scanf("%s", fed);
		strcpy((*B)->data.fed, fed);
		break;
	case 4:
		changeBirth(&(*B));
		break;
	case 5:
		changeFather(&(*B), T);
		break;

	case 7:return;
		break;
	}
	return;
}

void changeBirth(CSTree *A){
	printf("生日修改为:(请输入0~2021之间的整数)\n");
	int birth;
	fflush(stdin);
	scanf("%d", &birth);
	if (birth<0 || birth>2021){
		printf("输入有误\n");
		system("pause");
		return;
	}

	if ((*A)->father->data.seniority != 0 && (*A)->father->data.birth >= birth){
		printf("生日不能比父亲早\n");
		return;
	}
	(*A)->data.birth = birth;
	CSTree B;
	CSTree C = (*A)->father;
	if ((*A)->father->firstChild == (*A)){//用另外一个兄弟顶替，自己重新插入 
		(*A)->father->firstChild = (*A)->nextSibling;
		(*A)->nextSibling = NULL;
		(*A)->father = NULL;
	}
	else{
		for (B = (*A)->father->firstChild; B->nextSibling != (*A); B = B->nextSibling);//遍历找到自己的上一个兄弟，连接自己的下一个兄弟，自己重新插入 
		B->nextSibling = (*A)->nextSibling;
		(*A)->nextSibling = NULL;
		(*A)->father = NULL;
	}
	insertNode(&C, &(*A));
}

void changeFather(CSTree *A, CSForest T){
	printf("父亲修改为:\n");
	int birth = (*A)->data.birth;
	char name[100];
	fflush(stdin);
	scanf("%s", name);
	CSTree newFather = NULL;
	searchNode(T, name, &newFather);
	showMsg(&newFather);
	if (newFather == NULL){
		printf("不存在这个人\n");
		system("pause");
		return;
	}system("pause");
	if (newFather->data.birth >= birth){
		printf("生日不能比父亲早\n");
		return;
	}
	CSTree B;
	CSTree C = (*A)->father;
	if ((*A)->father->firstChild == (*A)){
		(*A)->father->firstChild = (*A)->nextSibling;//用另外一个兄弟顶替，自己重新插入 
		(*A)->nextSibling = NULL;
		(*A)->father = NULL;
	}
	else
	{
		B = (*A)->father->firstChild;
		for (; B->nextSibling != (*A); B = B->nextSibling);//遍历找到自己的上一个兄弟，连接自己的下一个兄弟，自己重新插入 
		B->nextSibling = (*A)->nextSibling;
		(*A)->nextSibling = NULL;
		(*A)->father = NULL;
	}

	insertNode(&newFather, &(*A));
	refreshSeniority(&T);
}








void SearchRel(){
	A = NULL;
	B = NULL;
	createCSTNode(&A);//年龄大信息 
	createCSTNode(&B); //年龄小信息
	char name[100];
	printf("请输入姓名1:");
	scanf("%s", name);
	searchNode(anc, name, &A);
	if (A->data.name == "NULL"){
		printf("不存在名为%s的人\n", name);
		return;
	}
	printf("请输入姓名2:");
	scanf("%s", name);
	searchNode(anc, name, &B);
	if (B->data.name == "NULL"){
		printf("不存在名为%s的人\n", name);
		A = NULL;
		return;
	}
	CSTree temp = NULL;
	if (A->data.birth>B->data.birth){
		temp = B;
		B = A;
		A = temp;
	}
	if ((B != anc) && A == B->father){
		printf("%s是%s的父亲\n", A->data.name, B->data.name);
		if (B->data.sex){
			printf("%s是%s的儿子\n", B->data.name, A->data.name);
		}
		else
		{
			printf("%s是%s的女儿\n", B->data.name, A->data.name);
		}
		printf("关系：三代内直系\n");
	}
	else if ((B != anc) && A == B->father->father){
		printf("%s是%s的爷爷\n", A->data.name, B->data.name);
		if (B->data.sex){
			printf("%s是%s的孙子\n", B->data.name, A->data.name);
		}
		else
		{
			printf("%s是%s的孙女\n", B->data.name, A->data.name);
		}
		printf("关系：三代内直系\n");
	}
	else if ((A->data.seniority >= 1 && B->data.seniority >= 1) && A->father->father == B->father->father){

		if (A->data.sex){
			printf("%s是%s的堂兄\n", A->data.name, B->data.name);
		}
		else
		{
			printf("%s是%s的堂姐\n", A->data.name, B->data.name);
		}
		if (B->data.sex){
			printf("%s是%s的堂弟\n", B->data.name, A->data.name);
		}
		else
		{
			printf("%s是%s的堂妹\n", B->data.name, A->data.name);
		}
		printf("关系：三代内旁系\n");
	}
	else if ((A->data.seniority >= 1 && B->data.seniority >= 1) && A->father == B->father->father){

		if (A->data.sex){
			printf("%s是%s的叔叔\n", A->data.name, B->data.name);
		}
		else
		{
			printf("%s是%s的姑妈\n", A->data.name, B->data.name);
		}
		if (B->data.sex){
			printf("%s是%s的侄子\n", B->data.name, A->data.name);
		}
		else
		{
			printf("%s是%s的侄女\n", B->data.name, A->data.name);
		}
		printf("关系：三代内旁系\n");
	}
	else
	{
		printf("关系：%s,%s两者非三代内旁系或直系\n", A->data.name, B->data.name);
	}
	A = NULL;
	B = NULL;
}


void inorderCousin(CSTree T, CSTree A){
	if (NULL == T)return;
	if (T->data.seniority >= 2)
	if (T->father->father == A->father->father&&T != A)
		printf("[%d|%d|%s]\n", T->data.seniority, T->data.birth, T->data.name);
	inorderCousin(T->firstChild, A);
	inorderCousin(T->nextSibling, A);
}





void relationship(){
	B = NULL;
	A = NULL;
	char name[100];
	printf("请输入姓名:");
	scanf("%s", name);
	searchNode(anc, name, &B);
	if (B == NULL){
		printf("不存在名为%s的人\n", name);
		return;
	}
	int choice;
	printf("该人信息如下：\n");
	showMsg(&B);
	printf("\n");
	printf("输入你想查询的关系\n");
	printf("\n");
	printf("********************************\n");
	printf("\n");
	printf("    1.祖先     2.后代\n");
	printf("\n");
	printf("    3.堂兄弟       4.结束程序\n");
	printf("\n");
	printf("********************************\n");
	printf("\n");
	printf("请输入序号：\n");
	fflush(stdin);
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		A = B->father;
		for (; A != NULL; A = A->father){
			printf("[%d|%d|%s]\n", A->data.seniority, A->data.birth, A->data.name);
		}
		break;
	case 2:
		if (B->firstChild==NULL){
			printf("其不存在后代！");
		}else{
			PrintTree(B->firstChild);
		}
		break;
	case 3:
		inorderCousin(anc, B);
	case 4:break;

	}
	B = NULL;
	A = NULL;
	return;
}

void PrintAsTree(CSTree T) {
	int cnt;
	if (T) {
		//输出空格
		for (cnt = 0; cnt<T->data.seniority; cnt++) printf("     ");
		//输出字符
		printf("[%d|%d|%s]\n", T->data.seniority, T->data.birth, T->data.name);
		printf("\n");
		PrintAsTree(T->firstChild);
		PrintAsTree(T->nextSibling);
	}
}

Status PrintTree(CSTree t){
	LinkList L;
	if (t->data.birth == 0){
		printf("  族谱不存在\n");
		return OK;
	}
	InitQueue(&L);//初始化队列 
	Traverse(t, L);//利用队列输出 
	DestroyQueue(L);//销毁队列 
	return OK;
}



Status Traverse(CSTree T, LinkList L){
	CSTree P = T;
	CSTree K;
	int i = 0;
	int j = 1;
	while (P)//p指向森林里的每棵树
	{
		//        printf("第%d个家族\n",j);
		K = P;//利用k来遍历以p为根节点子树中的节点
		Enqueue(L, K);//根节点入队
		while (IfEmpty(L) == FALSE)//只要队列不为空就依次出队直到队空
		{
			Dequeue(L, &K);
			if (i != K->data.seniority){
				printf("\n");
				i = K->data.seniority;
			}
			printf("[%d|%d|%s]", K->data.seniority, K->data.birth, K->data.name);
			if (K->firstChild){//如果该节点不是森林中的叶节点，则进入下一层
				K = K->firstChild;
				Enqueue(L, K);
				while (K->nextSibling)
				{//入队同层兄弟节点
					K = K->nextSibling;
					Enqueue(L, K);
				}
			}
		}
		P = P->nextSibling;
		printf("\n");
		j++;
	}

}


//初始化队列 
Status InitQueue(LinkList *L){
	(*L) = (LNode*)malloc(sizeof(LNode));//分配结点空间 
	if (*L == NULL) //分配失败              
		return OVERFLOW;
	(*L)->next = NULL;
	return OK;
}
//新建结点 
LNode* CreateNode(CSTNode *p){
	LNode *q;
	q = (LNode*)malloc(sizeof(LNode));//分配结点空间
	if (q != NULL){ //分配成功 
		q->data = p;
		q->next = NULL;
	}
	return q;
}
//元素q入队列
Status Enqueue(LNode *p, CSTNode *q){
	if (p == NULL)
		return ERROR;
	while (p->next != NULL) //调至队列最后 
		p = p->next;
	p->next = CreateNode(q);//生成结点让q进入队列 
	return OK;
}
//出队列，并以q返回值 
Status Dequeue(LNode *p, CSTree *q){
	LNode *aq;
	if (p == NULL || p->next == NULL) //删除位置不合理 
		return ERROR;
	aq = p->next;//修改被删结点aq的指针域
	p->next = aq->next;
	(*q) = aq->data;
	free(aq); //释放结点aq
	return OK;
}
//队列判空 
Status IfEmpty(LinkList L){
	if (L == NULL) //队列不存在 
		return ERROR;
	if (L->next == NULL)//队列为空 
		return TRUE;
	return FALSE;//队列非空 
}
//销毁队列 
void DestroyQueue(LinkList L){
	LinkList p;
	if (L != NULL){
		p = L;
		L = L->next;
		free(p); //逐一释放 
		DestroyQueue(L);
	}
}




