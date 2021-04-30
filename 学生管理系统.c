#include <stdio.h>

#include <stdlib.h>

#include <malloc.h>

#include <string.h>

typedef struct student

{

    int number;//学号,超过9位数字一般会乱码，太难解决了哈哈哈哈哈 

    char name[100];

    float maths;

    float computer;

    float English;

    struct student * next;

}STUDENT;

STUDENT * delete(STUDENT* head);

STUDENT * modify(STUDENT *head);

STUDENT * create_list();

STUDENT * sort();

STUDENT * insert(STUDENT *head);

STUDENT * query(STUDENT*head);

STUDENT * read(STUDENT * head);

int save(STUDENT * p);

void sort_output(STUDENT *head);

int all_student_number();

void swap(STUDENT *p1,STUDENT*p2);

float *average_maths1(STUDENT * head);

int main()

{
    int i;

    STUDENT * head = NULL;//创建链表头指针

    do

    {
    	printf("\n\n"); 
		//printf("                                          *欢迎使用五口巴大学学生管理系统*\n");
        printf("请输入功能序号（0--9)\n");
        printf("                                          *欢迎使用五口巴大学学生管理系统*\n");
        printf("                                         *1,覆盖或创建新文件存储学生信息*\n");
    	printf("                                  *      *2,增添学生信息*               *\n");
    	printf("                                 * *     *3,删除学生信息*;             * *\n");
    	printf("                                *   *    *4,仅对学生成绩进行修改      *   *\n");
    	printf("                                 * *     *5,通过学号查询学生成绩*      * *\n");
		printf("                                  *      *6,对学生成绩进行排序后输出*   *\n");
    	printf("                                         *7,加载保存的学生成绩*\n");
    	printf("                                         *8,统计平均分,不合格人数,某分数段下人数*\n");
    	printf("                                         *9,统计文件内学生个数*\n");
    	printf("                                         *0,退出程序*\n");

        scanf("%d",&i);

        switch(i)

        {

        case 0:

            break;

        case 1:

            head = create_list();

            break;

        case 2:

            head = insert(head);

            break;

        case 3:

            head = delete(head);
            break;

        case 4:

            head = modify(head);

            break;

        case 5:

            head = query(head);

            break;

        case 6:

            head = sort(head);

            break;

        case 7:

            read(head);

            break;
            
        case 8:
        	
        	average_maths1(head);
        	
        	break;
            
        case 9:
        	
        	printf("文件内学生个数有%d个\n",all_student_number());
        	
        	break;
        	

        default:

            printf("请输入有效的数字！\n");//这里若输入向上键会导致程序崩溃，目前原因未知(仅出现在linux上） 

            break;

        }

    }while(i!=0);

    return 0;

}




//一条分割线........................................................

STUDENT * modify(STUDENT *head)

{

	int sum1 = 0;//用于检测后面输入学号与文件内容不符时统计

    FILE *fp;

    int student_number;

    char file_path[100];

    STUDENT * p1 = (STUDENT*)malloc(sizeof(STUDENT));

    head = p1;

    printf("请输入存储学生信息的文件名称(与程序在同\n一文件夹内输入文件名，否则输入绝对路径)\n");

    scanf("%s",file_path);

    if((fp=fopen(file_path,"r"))==NULL)

    {

        printf("打不开此文件，请输入有效的文件名称\n");
        
        return 0;

    }

    do

    {

        STUDENT * p2 = (STUDENT*)malloc(sizeof(STUDENT));

        fscanf(fp,"%d\t%s\t%f\t%f\t%f\t\n",&p2->number,p2->name,&p2->computer,&p2->maths,&p2->English);//读取数据

        p1->next = p2;

        p2->next = NULL;

        p1 = p2;

    }while(!feof(fp));

    printf("被修改学生的学号是?\n");

    scanf("%d",&student_number);

    STUDENT * p3 = head;

    while(p3->next!=NULL)

    {

        p3 = p3->next;//整个链表前移一位

        if(p3->number == student_number){

            int function;

            int grade;

            char student_name[200];

            printf("你需要修改哪项成绩？（输入你需要的功能序号）\n1,计算机\n2,高数\n 3,大英\n4,学生姓名\n");

            scanf("%d",&function);

            switch(function)

            {

            case 1:

                printf("输入更改后的计算机成绩\n");

                scanf("%d",&grade);

                p3->computer = grade;
                //使头指针指向新数据，达成修改目的 

                save(head);

    			fclose(fp);

    			return head;

            case 2:

                printf("输入更改后的高数成绩\n");

                scanf("%d",&grade);

                p3->maths = grade;

                save(head);

    			fclose(fp);

    			return head;

            case 3:

                printf("输入更改后的大英成绩\n");

                scanf("%d",&grade);

                p3->English = grade;

                save(head);

    			fclose(fp);

    			return head;

            case 4:

                printf("输入更改后的学生姓名\n");

                scanf("%s",student_name);
                
                strcpy(p3->name,student_name);

                save(head);

    			fclose(fp);

    			return head;

            default:

                save(head);

    			fclose(fp);

    			return head;

            }

        }

    }
    
    if(p3->next == NULL){
    	
    	printf("没有找到该学号\n");
    	
    	fclose(fp);

    	return head;
	}

    save(head);//目的是让头指针顺着链表保留所有文件,这三行做个保险，不建议改动，代码靠bug运行 

    fclose(fp);

    return head;

}




//一条分割线.................................................................


STUDENT * insert(STUDENT *head)//输入英文会导致程序跳跃，未修复 

{

    FILE *fp;

    char file_path[100];

    int student_number,i;

    printf("你需要插入多少个学生的信息？\n");//这一步后面要做个统计，暂时还没做哈哈哈

    scanf("%d",&student_number);

    printf("请输入存储学生信息的文件名称(与程序在同\n一文件夹内输入文件名，否则输入绝对路径)\n");

    scanf("%s",file_path);

    for(i=0;i<student_number;i++)

    {

        if((fp=fopen(file_path,"a"))==NULL)

        {

            printf("无法打开此文件，请输入有效文件名\n");

        }

        fseek(fp,0,SEEK_END);//将文件指针指向文件的尾部

        STUDENT * p2 = (STUDENT *)malloc(sizeof(STUDENT));//创建一个新的节点储存需要插入的数据,这是个新函数，所以要重新来个p2

        printf("请输入学生的姓名：\n");

        scanf("%s",file_path);

        strcpy(p2->name,file_path);

        printf("请输入学生的学号：\n");

        scanf("%d",&p2->number);

        printf("请依次输入学生的计算机，高数，大英成绩\n");

        scanf("%f %f %f",&p2->computer,&p2->maths,&p2->English);

        fprintf(fp,"%d\t%s\t%f\t%f\t%f\t\n",p2->number,p2->name,p2->computer,p2->maths,p2->English);

    }

    fclose(fp);

    return head;

}




//一条分割线............................................................................

STUDENT * create_list()

{

    int length,i;

    char NAME[200];

    STUDENT * head = NULL;

    STUDENT * p1 = (STUDENT * )malloc(sizeof(STUDENT));

    head = p1;

    printf("你需要存入多少学生的信息？\n");

    scanf("%d",&length);

    for(i = 0;i<length;i++)

    {

        STUDENT * p2 = (STUDENT*)malloc(sizeof(STUDENT));

        printf("请输入学生的姓名：\n");

        scanf("%s",NAME);

        strcpy(p2->name,NAME);//将名字复制到p2中，相当于储存数据在文件中

        printf("请输入学生的学号：\n");

        scanf("%d",&p2->number);

        printf("请依次输入学生的计算机，高数，大英成绩:\n");

        scanf("%f %f %f",&p2->computer,&p2->maths,&p2->English);

        //头节点的下一个位置是新创建的节点，这里之前已经将p1指向了头节点

        p1->next = p2;

        //新创建的节点的下一个位置置为空，代表是链表的尾部

        p2->next = NULL;

        p1 = p2;//这里是将p2替换掉p1,因为p1无数据，p2有数据，有利于保存文件
		//这里的循环很重要，因为p2指向null，所以p2下一步是表尾，p1=p2即将p1移动到表尾，
		//随后只要不断改变p2所指向构造中的变量，就可以不断的将数据录入链表。
		 
    }

    save(head);

    //返回头指针

    return head;

}





//一条分割线............................................................................ 
STUDENT * delete(STUDENT* head)

{
	int sum1 = 0;//用于检测后面输入学号与文件内容不符时统计 

    FILE *fp;

    int storage_number;

    char file_path[100];

    STUDENT * p1 = (STUDENT*)malloc(sizeof(STUDENT));

    head = p1;

    printf("请输入存储学生信息的文件名称(与程序在同\n一文件夹内输入文件名，否则输入绝对路径)\n");

    scanf("%s",file_path);

    if((fp=fopen(file_path,"r"))==NULL)

    {

        printf("无法打开此文件，请输入有效文件名\n");
        
        return 0;

    }

    do

    {

        STUDENT * p2 = (STUDENT*)malloc(sizeof(STUDENT));

        fscanf(fp,"%d\t%s\t%f\t%f\t%f\t\n",&p2->number,p2->name,&p2->computer,&p2->maths,&p2->English);
        //读取文件内容用fscanf 

        p1->next = p2;

        p2->next = NULL;

        p1 = p2;

    }while(!feof(fp));

    printf("被删除学生信息的学号是？\n");

    scanf("%d",&storage_number);

    STUDENT * p3 = head;

    while(p3->next!=NULL)//循环,一直走到p3走到最后一个数字，相当于遍历了链表

    {

        if(p3->next->number == storage_number && p3->next->next!=NULL) 

        {

            STUDENT *p4 = p3->next;

            p3->next = p3->next->next;//链表的删除

            free(p4);

            break;

        }

        else if(p3->next->number == storage_number && p3->next->next == NULL)/*即要删除的学号是链表的最后一位
        																		又或者说遍历到了最后一个数据要
																				退出程序了*/ 

        {

            STUDENT * p4 = p3->next;

            free(p4);

            p3->next = NULL;

            save(head);
            
            printf("学生信息删除成功\n");

    		fclose(fp);

   			return head;//为了不让sum1++，return head可以直接退出此程序 

        }

        p3 = p3->next;
        
        sum1 ++;//sum1++即上面遍历中没有与指定学号相符的，有助于下面输出没有找到该学号 

    }
    
    int a = all_student_number();//a为学生人数,这里调用了另外一个函数 
    
    if(sum1 == a){
    	
    	printf("没有找到该学号，请重新输入\n");
    	
    	fclose(fp);

    	return head;
    	
	}

    save(head);//这三行为了保险，建议别改，此代码靠bug相互制衡以运行 

    fclose(fp);

    return head;

}


//一条分割线............................................................................
STUDENT *read(STUDENT * head)

{

    STUDENT * p1 = (STUDENT*)malloc(sizeof(STUDENT));

    head = p1;

    FILE *fp;

    char file_path[200];

    printf("请输入存储学生信息的文件名称(与程序在同\n一文件夹内输入文件名，否则输入绝对路径)\n");

    scanf("%s",file_path);

    if((fp=fopen(file_path,"r"))==NULL)

    {

        printf("无法打开此文件，请输入有效的文件名称\n");

        return 0;

    }

    do

    {

        STUDENT * p2 = (STUDENT*)malloc(sizeof(STUDENT));

        fscanf(fp,"%d\t%s\t%f\t%f\t%f\t\n",&p2->number,p2->name,&p2->computer,&p2->maths,&p2->English);

        printf("%d\t%s\t%f\t%f\t%f\t\n",p2->number,p2->name,p2->computer,p2->maths,p2->English);
        //遍历链表输出 

        p1->next = p2;

        p2->next = NULL;

        p1 = p2;

    }while(!feof(fp));

    fclose(fp);

    return head;

}




//一条分割线............................................................................


STUDENT * query(STUDENT *head)

{
	
	int sum1 = 0;//用于检测后面输入学号与文件内容不符时统计 
	
    FILE *fp;

    int student_number;

    char file_path[100];

    STUDENT * p1 = (STUDENT*)malloc(sizeof(STUDENT));

    head = p1;

    printf("请输入存储学生信息的文件名称(与程序在同\n一文件夹内输入文件名，否则输入绝对路径)\n");

    scanf("%s",file_path);

    if((fp=fopen(file_path,"r"))==NULL)


    {

        printf("无法打开文件，请输入正确的文件名称\n");
        
        return 0;

    }

    do

    {
//读取文件内所有数据 
        STUDENT * p2 = (STUDENT*)malloc(sizeof(STUDENT));

        fscanf(fp,"%d\t%s\t%f\t%f\t%f\t\n",&p2->number,p2->name,&p2->computer,&p2->maths,&p2->English);

        p1->next = p2;

        p2->next = NULL;

        p1 = p2;

    }while(!feof(fp));

    printf("输入你要查询的学生的学号\n");

    scanf("%d",&student_number);

    STUDENT * p3 = head;

    while(p3->next!=NULL)//遍历文件寻找与学号相符的数据 

    {

        p3 = p3->next;

        if(p3->number == student_number){

            int function;

            printf("请输入你需要的功能序号:\n1,计算机\n2,数学\n3,英语\n4,学生姓名\n5,学生的全部信息\n");

            scanf("%d",&function);

            switch(function)

            {

            case 1:

                printf("计算机成绩为%f\n",p3->computer);

                return 0;/*因为这个模块是一个函数,所以return不会退出 main函数，这里用return是为了
						 能为下面的sum1做统计排除输入时非文件内学号的问题*/ 

            case 2:

                printf("高数成绩是%f\n",p3->maths);

                return 0;

            case 3:

                printf("大英成绩是:%f\n",p3->English);

                return 0;

            case 4:

                printf("该学生姓名是:%s\n",p3->name);

                return 0;

            case 5:

                printf("计算机成绩为%f\n",p3->computer);

                printf("高数成绩为%f\n",p3->maths);

                printf("大英成绩为%f\n",p3->English);

                printf("该同学的名字是:%s\n",p3->name);
                
                return 0;

            default:

                return 0;

            }

        }
        
		sum1++;

    }
    
    int a = all_student_number();//a为学生人数,这里调用了另外一个函数 
    
    if(sum1 == a){
    	
    	printf("没有找到该学号，请重新输入");
    	
	}

    fclose(fp);

    return head;

}


//一条分割线............................................................................


STUDENT * sort()

{

    FILE *fp;

    STUDENT * head = NULL;

    int function;

    float sum,sum1;

    char file_path[100];

    STUDENT * p1 = (STUDENT*)malloc(sizeof(STUDENT));

    head = p1;

    printf("请输入存储学生信息的文件名称(与程序在同\n一文件夹内输入文件名，否则输入绝对路径)\n");

    scanf("%s",file_path);

    if((fp=fopen(file_path,"r"))==NULL)

    {

        printf("无法打开文件，请输入有效的文件名称\n");
        
        return 0;

    }

    do//循环

    {

        STUDENT * p2 = (STUDENT*)malloc(sizeof(STUDENT));

        fscanf(fp,"%d\t%s\t%f\t%f\t%f\t\n",&p2->number,p2->name,&p2->computer,&p2->maths,&p2->English);

        p1->next = p2;

        p2->next = NULL;

        p1 = p2;

    }while(!feof(fp));

    printf("请输入你需要的功能序号(排序科目)：\n1,计算机\n2,高数\n3,大英\n4,总分：\n");

    scanf("%d",&function);

    //创建两个指针，用于循环,p3变为头指针的下一部是为了遍历,p4的赋值随意，因为后面会对p4再赋值

    STUDENT * p4 = NULL;

    STUDENT * p3 = head->next;

    switch(function)

    {

    case 1:

        //这里可以再改进下算法

        while(p3->next!=NULL)

        {

            p4=head->next;

            while(p4->next!=NULL)

            {

                if(p4->computer < p4->next->computer)

                    swap(p4,p4->next);

                p4=p4->next;

            }

            p3=p3->next;

        }

        sort_output(head);


        break;

    case 2:

        while(p3->next!=NULL)

        {

            p4=head->next;

            while(p4->next!=NULL)

            {

                if(p4->maths < p4->next->maths)

                    swap(p4,p4->next);

                p4=p4->next;

            }

            p3=p3->next;

        }

        sort_output(head);

        break;

    case 3:

        while(p3->next!=NULL)

        {

            p4=head->next;

            while(p4->next!=NULL)

            {

                if(p4->English < p4->next->English)

                    swap(p4,p4->next);

                p4=p4->next;

            }

            p3=p3->next;

        }

        sort_output(head);

        break;

    case 4:

        while(p3->next!=NULL)

        {

            p4=head->next;

            while(p4->next!=NULL)

            {

                sum = p4->computer + p4->maths + p4->English;

                sum1 = p4->next->computer + p4->next->maths + p4->next->English;

                if(sum < sum1)

                    swap(p4,p4->next);

                p4=p4->next;

            }

            p3=p3->next;

        }

        sort_output(head);

        break;

    default:
    	
    	printf("请输入有效的功能序号\n");

        break;


    }

    fclose(fp);

    return head;

}


//一条分割线............................................................................
void swap(STUDENT *p1,STUDENT*p2)

{

    float temporary;

    char student_name[200];

    temporary = p1->computer;

    p1->computer = p2->computer;

    p2->computer = temporary;

    temporary = p1->maths;

    p1->maths = p2->maths;

    p2->maths = temporary;



    temporary = p1->English;

    p1->English = p2->English;

    p2->English = temporary;




    temporary = p1->number;

    p1->number = p2->number;

    p2->number = temporary;



    strcpy(student_name,p1->name);

    strcpy(p1->name,p2->name);

    strcpy(p2->name,student_name);

}





//一条分割线............................................................................

int save(STUDENT * p)

{

    p=p->next;

    FILE *fp;

    char file_path[200];

    printf("你要将文件保存在哪里?(若文件不存在则会创建一个新文件,对文件\n和此程序的建议是放在同一文件夹内，否则寻找时要输入绝对路径)\n");

    scanf("%s",file_path);

    //以写的形式打开文件,注意打开文件的方式要适当的选择

    if((fp = fopen(file_path,"w"))==NULL)

    {

        printf("无法打开此文件，请输入有效的文件地址\n");

        return 0;

    }

    while(p!=NULL)


    {

        fprintf(fp,"%d\t%s\t%f\t%f\t%f\t\n",p->number,p->name,p->computer,p->maths,p->English);
        //将数据写入文件用fprintf 

        p = p->next;

    }

    fclose(fp);

    return 0;

}






//一条分割线............................................................................


void sort_output(STUDENT *head)

{

    //遍历链表

    printf("排序后的结果如下\n");

    STUDENT * p = head->next;

    while(p!=NULL)

    {

        printf("%d\t%s\t%f\t%f\t%f\t\n",p->number,p->name,p->computer,p->maths,p->English);

        p=p->next;

    }

}




//一条分割线...................................................................................... 
//对文件的建议，放在同一文件夹内，否则要输入绝对路径 
//学生个数(本质上是统计行数,返回值为学生总数)
int all_student_number()

{
	
    FILE *pf = fopen("data.txt", "r"); // 打开文件,这里默认是在同一文件夹内，且确定了文件，可以再改一下，还没改 
    
    char buf[1000];
    
    int lineCnt = 0;
    
    if (!pf) {// 判断是否打开成功
    
        printf("无法打开此文件，请输入有效的文件地址\n");

        return 0;
        
    }
        
    while (fgets(buf, 1000, pf)) // fgets循环读取，直到文件最后，才会返回NULL
    
        lineCnt++; // 累计行数
        
    fclose(pf);
    
    return lineCnt;
    
}



//一条分割线.......................................................................................................... 
//总成绩和平均成绩 
float *average_maths1(STUDENT * head){

    STUDENT * p1 = (STUDENT*)malloc(sizeof(STUDENT));

    head = p1;

    FILE *fp;

    char file_path[200];

    printf("请输入存储学生信息的文件名称(与程序在同\n一文件夹内输入文件名，否则输入绝对路径)\n");

    scanf("%s",file_path);

    if((fp=fopen(file_path,"r"))==NULL)

    {

        printf("无法打开此文件，请输入有效的文件名称\n");

        return 0;

    }
    
    float all_maths,all_computer,all_English,all_grade,all_grade_tempory;//这里的grade不加s 
    
    float average_maths,average_English,average_computer;
	
	int sum_maths,sum_English,sum_computer,sum_grade;   
	 
    all_maths=all_computer=all_English=all_grade=all_grade_tempory=0;
    
    average_maths=average_English=average_computer=0;
    
    sum_maths=sum_English=sum_computer=sum_grade=0;
  
    
//询问是否需要统计各分数段人数 
	int w,sum_people,m,E,c,b;
	
	w=sum_people=m=E=c=b=0;
	
    printf("是否需要统计某分数段人数?\n1:是,2:否\n");
    
    scanf("%d",&w);
    
    if(w==1){
    	
    	int a;
    	
    	printf("你要统计什么科目?\n1,计算机\n2,高数\n3,大英\n0,退出程序\n");
    	
    	scanf("%d",&a);
    	
    	switch(a){
    		
    		case 0:
    			
    			break;
    			
    		case 1:
    			
    			c=1;
    			
    			printf("输入最高分数，统计该分数以下的人\n");
    			
    			scanf("%d",&b);
    			
    			//printf("%d",sum_people_computer);
    			
    			break;
    		
    		case 2:
    			
    			m=1;
    			
    			printf("输入最高分数，统计该分数以下的人\n");
    			
    			scanf("%d",&b);
    			
    			//printf("%d",sum_people_maths);
    			
    			break;
    			
    		case 3:
    			
    			E=1;
    			
    			printf("输入最高分数，统计该分数以下的人\n");
    			
    			scanf("%d",&b);
    			
    			//printf("%d",sum_people_English);
    			
    			break;
    			
		}
    	
	}
	

    do{
		//总成绩模块 
        STUDENT * p2 = (STUDENT*)malloc(sizeof(STUDENT));

        fscanf(fp,"%d\t%s\t%f\t%f\t%f\t\n",&p2->number,p2->name,&p2->computer,&p2->maths,&p2->English);
        
        all_maths += p2->maths;
        
		all_computer += p2->computer;
		
		all_English += p2->English;
		
		all_grade += p2->maths+p2->computer+p2->English;
		
		all_grade_tempory = p2->maths+p2->computer+p2->English;
		
		
//统计及格人数...............................................可以拿来再做指定分数段的功能 
		
		if(p2->maths < 60){
        	
        	sum_maths++;
        	
		}
		
		if(p2->English < 60){
        	
        	sum_English++;
        	
		}
		
		if(p2->computer < 60){
        	
        	sum_computer++;
    	}
    	
    	if(all_grade_tempory < 180){ //这里不应该用all_grade.....................................要改啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊 
        	
        	sum_grade++;
    	}
    	
//做一个统计各分数段的人数功能,后面可以用if来询问是否需要此功能，用空间换时间吧..................................................................................
		if(c==1){
			
			if(p2->computer<b){
				
				sum_people++;
				
			}
			
		}
		
		if(m==1){
			
			if(p2->maths<b){
				
				sum_people++;
				
			}
			
		}
		
		if(E==1){
			
			if(p2->English<b){
				
				sum_people++;
				
			}
			
		}

		
		
		
		p1->next = p2;

        p2->next = NULL;

        p1 = p2;

    }while(!feof(fp));
    
//输出分数段 
    if (w==1){
    	
    	printf("该分数之下有%d个人\n",sum_people);
    	
	}
    
//分割线............. 
    
    int a = all_student_number();//a为学生人数
    
    average_maths=all_maths/a;
    
    average_computer=all_computer/a;
    
    average_English=all_English/a;
    		
	//平均成绩和合格人数 
		
	int function=0; 
		
	printf("你想要查看哪科成绩的平均分和不合格人数?(输入功能序号)\n");
		
	printf("1,高数\n2,计算机\n3,大英\n4,全科\n0,退出程序\n");
		
	scanf("%d",&function);
		
	switch(function){
			
		case 1:
				
			printf("average_maths=%f\n",all_maths/a);
				
			printf("不及格人数为%d\n及格人数为%d\n",sum_maths,a-sum_maths);
			
			break;
			
		case 2:
				
			printf("average_computer=%f\n",all_computer/a);
				
			printf("不及格人数为%d\n及格人数为%d\n",sum_computer,a-sum_computer);
			
			break;
				
		case 3:
				
			printf("average_English=%f\n",all_English/a);
				
			printf("不及格人数为%d\n及格人数为%d\n",sum_English,a-sum_English);
			
			break;
				
		case 4:
				
			printf("average_grades=%f\n",all_grade/a);
				
			printf("不及格人数为%d\n及格人数为%d\n",sum_grade,a-sum_grade);
			
			break;
				
	}

    fclose(fp);

    return head;

}







 
