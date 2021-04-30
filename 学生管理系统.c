#include <stdio.h>

#include <stdlib.h>

#include <malloc.h>

#include <string.h>

typedef struct student

{

    int number;//ѧ��,����9λ����һ������룬̫�ѽ���˹��������� 

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

    STUDENT * head = NULL;//��������ͷָ��

    do

    {
    	printf("\n\n"); 
		//printf("                                          *��ӭʹ����ڰʹ�ѧѧ������ϵͳ*\n");
        printf("�����빦����ţ�0--9)\n");
        printf("                                          *��ӭʹ����ڰʹ�ѧѧ������ϵͳ*\n");
        printf("                                         *1,���ǻ򴴽����ļ��洢ѧ����Ϣ*\n");
    	printf("                                  *      *2,����ѧ����Ϣ*               *\n");
    	printf("                                 * *     *3,ɾ��ѧ����Ϣ*;             * *\n");
    	printf("                                *   *    *4,����ѧ���ɼ������޸�      *   *\n");
    	printf("                                 * *     *5,ͨ��ѧ�Ų�ѯѧ���ɼ�*      * *\n");
		printf("                                  *      *6,��ѧ���ɼ�������������*   *\n");
    	printf("                                         *7,���ر����ѧ���ɼ�*\n");
    	printf("                                         *8,ͳ��ƽ����,���ϸ�����,ĳ������������*\n");
    	printf("                                         *9,ͳ���ļ���ѧ������*\n");
    	printf("                                         *0,�˳�����*\n");

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
        	
        	printf("�ļ���ѧ��������%d��\n",all_student_number());
        	
        	break;
        	

        default:

            printf("��������Ч�����֣�\n");//�������������ϼ��ᵼ�³��������Ŀǰԭ��δ֪(��������linux�ϣ� 

            break;

        }

    }while(i!=0);

    return 0;

}




//һ���ָ���........................................................

STUDENT * modify(STUDENT *head)

{

	int sum1 = 0;//���ڼ���������ѧ�����ļ����ݲ���ʱͳ��

    FILE *fp;

    int student_number;

    char file_path[100];

    STUDENT * p1 = (STUDENT*)malloc(sizeof(STUDENT));

    head = p1;

    printf("������洢ѧ����Ϣ���ļ�����(�������ͬ\nһ�ļ����������ļ����������������·��)\n");

    scanf("%s",file_path);

    if((fp=fopen(file_path,"r"))==NULL)

    {

        printf("�򲻿����ļ�����������Ч���ļ�����\n");
        
        return 0;

    }

    do

    {

        STUDENT * p2 = (STUDENT*)malloc(sizeof(STUDENT));

        fscanf(fp,"%d\t%s\t%f\t%f\t%f\t\n",&p2->number,p2->name,&p2->computer,&p2->maths,&p2->English);//��ȡ����

        p1->next = p2;

        p2->next = NULL;

        p1 = p2;

    }while(!feof(fp));

    printf("���޸�ѧ����ѧ����?\n");

    scanf("%d",&student_number);

    STUDENT * p3 = head;

    while(p3->next!=NULL)

    {

        p3 = p3->next;//��������ǰ��һλ

        if(p3->number == student_number){

            int function;

            int grade;

            char student_name[200];

            printf("����Ҫ�޸�����ɼ�������������Ҫ�Ĺ�����ţ�\n1,�����\n2,����\n 3,��Ӣ\n4,ѧ������\n");

            scanf("%d",&function);

            switch(function)

            {

            case 1:

                printf("������ĺ�ļ�����ɼ�\n");

                scanf("%d",&grade);

                p3->computer = grade;
                //ʹͷָ��ָ�������ݣ�����޸�Ŀ�� 

                save(head);

    			fclose(fp);

    			return head;

            case 2:

                printf("������ĺ�ĸ����ɼ�\n");

                scanf("%d",&grade);

                p3->maths = grade;

                save(head);

    			fclose(fp);

    			return head;

            case 3:

                printf("������ĺ�Ĵ�Ӣ�ɼ�\n");

                scanf("%d",&grade);

                p3->English = grade;

                save(head);

    			fclose(fp);

    			return head;

            case 4:

                printf("������ĺ��ѧ������\n");

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
    	
    	printf("û���ҵ���ѧ��\n");
    	
    	fclose(fp);

    	return head;
	}

    save(head);//Ŀ������ͷָ��˳�������������ļ�,�������������գ�������Ķ������뿿bug���� 

    fclose(fp);

    return head;

}




//һ���ָ���.................................................................


STUDENT * insert(STUDENT *head)//����Ӣ�Ļᵼ�³�����Ծ��δ�޸� 

{

    FILE *fp;

    char file_path[100];

    int student_number,i;

    printf("����Ҫ������ٸ�ѧ������Ϣ��\n");//��һ������Ҫ����ͳ�ƣ���ʱ��û��������

    scanf("%d",&student_number);

    printf("������洢ѧ����Ϣ���ļ�����(�������ͬ\nһ�ļ����������ļ����������������·��)\n");

    scanf("%s",file_path);

    for(i=0;i<student_number;i++)

    {

        if((fp=fopen(file_path,"a"))==NULL)

        {

            printf("�޷��򿪴��ļ�����������Ч�ļ���\n");

        }

        fseek(fp,0,SEEK_END);//���ļ�ָ��ָ���ļ���β��

        STUDENT * p2 = (STUDENT *)malloc(sizeof(STUDENT));//����һ���µĽڵ㴢����Ҫ���������,���Ǹ��º���������Ҫ��������p2

        printf("������ѧ����������\n");

        scanf("%s",file_path);

        strcpy(p2->name,file_path);

        printf("������ѧ����ѧ�ţ�\n");

        scanf("%d",&p2->number);

        printf("����������ѧ���ļ��������������Ӣ�ɼ�\n");

        scanf("%f %f %f",&p2->computer,&p2->maths,&p2->English);

        fprintf(fp,"%d\t%s\t%f\t%f\t%f\t\n",p2->number,p2->name,p2->computer,p2->maths,p2->English);

    }

    fclose(fp);

    return head;

}




//һ���ָ���............................................................................

STUDENT * create_list()

{

    int length,i;

    char NAME[200];

    STUDENT * head = NULL;

    STUDENT * p1 = (STUDENT * )malloc(sizeof(STUDENT));

    head = p1;

    printf("����Ҫ�������ѧ������Ϣ��\n");

    scanf("%d",&length);

    for(i = 0;i<length;i++)

    {

        STUDENT * p2 = (STUDENT*)malloc(sizeof(STUDENT));

        printf("������ѧ����������\n");

        scanf("%s",NAME);

        strcpy(p2->name,NAME);//�����ָ��Ƶ�p2�У��൱�ڴ����������ļ���

        printf("������ѧ����ѧ�ţ�\n");

        scanf("%d",&p2->number);

        printf("����������ѧ���ļ��������������Ӣ�ɼ�:\n");

        scanf("%f %f %f",&p2->computer,&p2->maths,&p2->English);

        //ͷ�ڵ����һ��λ�����´����Ľڵ㣬����֮ǰ�Ѿ���p1ָ����ͷ�ڵ�

        p1->next = p2;

        //�´����Ľڵ����һ��λ����Ϊ�գ������������β��

        p2->next = NULL;

        p1 = p2;//�����ǽ�p2�滻��p1,��Ϊp1�����ݣ�p2�����ݣ������ڱ����ļ�
		//�����ѭ������Ҫ����Ϊp2ָ��null������p2��һ���Ǳ�β��p1=p2����p1�ƶ�����β��
		//���ֻҪ���ϸı�p2��ָ�����еı������Ϳ��Բ��ϵĽ�����¼������
		 
    }

    save(head);

    //����ͷָ��

    return head;

}





//һ���ָ���............................................................................ 
STUDENT * delete(STUDENT* head)

{
	int sum1 = 0;//���ڼ���������ѧ�����ļ����ݲ���ʱͳ�� 

    FILE *fp;

    int storage_number;

    char file_path[100];

    STUDENT * p1 = (STUDENT*)malloc(sizeof(STUDENT));

    head = p1;

    printf("������洢ѧ����Ϣ���ļ�����(�������ͬ\nһ�ļ����������ļ����������������·��)\n");

    scanf("%s",file_path);

    if((fp=fopen(file_path,"r"))==NULL)

    {

        printf("�޷��򿪴��ļ�����������Ч�ļ���\n");
        
        return 0;

    }

    do

    {

        STUDENT * p2 = (STUDENT*)malloc(sizeof(STUDENT));

        fscanf(fp,"%d\t%s\t%f\t%f\t%f\t\n",&p2->number,p2->name,&p2->computer,&p2->maths,&p2->English);
        //��ȡ�ļ�������fscanf 

        p1->next = p2;

        p2->next = NULL;

        p1 = p2;

    }while(!feof(fp));

    printf("��ɾ��ѧ����Ϣ��ѧ���ǣ�\n");

    scanf("%d",&storage_number);

    STUDENT * p3 = head;

    while(p3->next!=NULL)//ѭ��,һֱ�ߵ�p3�ߵ����һ�����֣��൱�ڱ���������

    {

        if(p3->next->number == storage_number && p3->next->next!=NULL) 

        {

            STUDENT *p4 = p3->next;

            p3->next = p3->next->next;//�����ɾ��

            free(p4);

            break;

        }

        else if(p3->next->number == storage_number && p3->next->next == NULL)/*��Ҫɾ����ѧ������������һλ
        																		�ֻ���˵�����������һ������Ҫ
																				�˳�������*/ 

        {

            STUDENT * p4 = p3->next;

            free(p4);

            p3->next = NULL;

            save(head);
            
            printf("ѧ����Ϣɾ���ɹ�\n");

    		fclose(fp);

   			return head;//Ϊ�˲���sum1++��return head����ֱ���˳��˳��� 

        }

        p3 = p3->next;
        
        sum1 ++;//sum1++�����������û����ָ��ѧ������ģ��������������û���ҵ���ѧ�� 

    }
    
    int a = all_student_number();//aΪѧ������,�������������һ������ 
    
    if(sum1 == a){
    	
    	printf("û���ҵ���ѧ�ţ�����������\n");
    	
    	fclose(fp);

    	return head;
    	
	}

    save(head);//������Ϊ�˱��գ������ģ��˴��뿿bug�໥�ƺ������� 

    fclose(fp);

    return head;

}


//һ���ָ���............................................................................
STUDENT *read(STUDENT * head)

{

    STUDENT * p1 = (STUDENT*)malloc(sizeof(STUDENT));

    head = p1;

    FILE *fp;

    char file_path[200];

    printf("������洢ѧ����Ϣ���ļ�����(�������ͬ\nһ�ļ����������ļ����������������·��)\n");

    scanf("%s",file_path);

    if((fp=fopen(file_path,"r"))==NULL)

    {

        printf("�޷��򿪴��ļ�����������Ч���ļ�����\n");

        return 0;

    }

    do

    {

        STUDENT * p2 = (STUDENT*)malloc(sizeof(STUDENT));

        fscanf(fp,"%d\t%s\t%f\t%f\t%f\t\n",&p2->number,p2->name,&p2->computer,&p2->maths,&p2->English);

        printf("%d\t%s\t%f\t%f\t%f\t\n",p2->number,p2->name,p2->computer,p2->maths,p2->English);
        //����������� 

        p1->next = p2;

        p2->next = NULL;

        p1 = p2;

    }while(!feof(fp));

    fclose(fp);

    return head;

}




//һ���ָ���............................................................................


STUDENT * query(STUDENT *head)

{
	
	int sum1 = 0;//���ڼ���������ѧ�����ļ����ݲ���ʱͳ�� 
	
    FILE *fp;

    int student_number;

    char file_path[100];

    STUDENT * p1 = (STUDENT*)malloc(sizeof(STUDENT));

    head = p1;

    printf("������洢ѧ����Ϣ���ļ�����(�������ͬ\nһ�ļ����������ļ����������������·��)\n");

    scanf("%s",file_path);

    if((fp=fopen(file_path,"r"))==NULL)


    {

        printf("�޷����ļ�����������ȷ���ļ�����\n");
        
        return 0;

    }

    do

    {
//��ȡ�ļ����������� 
        STUDENT * p2 = (STUDENT*)malloc(sizeof(STUDENT));

        fscanf(fp,"%d\t%s\t%f\t%f\t%f\t\n",&p2->number,p2->name,&p2->computer,&p2->maths,&p2->English);

        p1->next = p2;

        p2->next = NULL;

        p1 = p2;

    }while(!feof(fp));

    printf("������Ҫ��ѯ��ѧ����ѧ��\n");

    scanf("%d",&student_number);

    STUDENT * p3 = head;

    while(p3->next!=NULL)//�����ļ�Ѱ����ѧ����������� 

    {

        p3 = p3->next;

        if(p3->number == student_number){

            int function;

            printf("����������Ҫ�Ĺ������:\n1,�����\n2,��ѧ\n3,Ӣ��\n4,ѧ������\n5,ѧ����ȫ����Ϣ\n");

            scanf("%d",&function);

            switch(function)

            {

            case 1:

                printf("������ɼ�Ϊ%f\n",p3->computer);

                return 0;/*��Ϊ���ģ����һ������,����return�����˳� main������������return��Ϊ��
						 ��Ϊ�����sum1��ͳ���ų�����ʱ���ļ���ѧ�ŵ�����*/ 

            case 2:

                printf("�����ɼ���%f\n",p3->maths);

                return 0;

            case 3:

                printf("��Ӣ�ɼ���:%f\n",p3->English);

                return 0;

            case 4:

                printf("��ѧ��������:%s\n",p3->name);

                return 0;

            case 5:

                printf("������ɼ�Ϊ%f\n",p3->computer);

                printf("�����ɼ�Ϊ%f\n",p3->maths);

                printf("��Ӣ�ɼ�Ϊ%f\n",p3->English);

                printf("��ͬѧ��������:%s\n",p3->name);
                
                return 0;

            default:

                return 0;

            }

        }
        
		sum1++;

    }
    
    int a = all_student_number();//aΪѧ������,�������������һ������ 
    
    if(sum1 == a){
    	
    	printf("û���ҵ���ѧ�ţ�����������");
    	
	}

    fclose(fp);

    return head;

}


//һ���ָ���............................................................................


STUDENT * sort()

{

    FILE *fp;

    STUDENT * head = NULL;

    int function;

    float sum,sum1;

    char file_path[100];

    STUDENT * p1 = (STUDENT*)malloc(sizeof(STUDENT));

    head = p1;

    printf("������洢ѧ����Ϣ���ļ�����(�������ͬ\nһ�ļ����������ļ����������������·��)\n");

    scanf("%s",file_path);

    if((fp=fopen(file_path,"r"))==NULL)

    {

        printf("�޷����ļ�����������Ч���ļ�����\n");
        
        return 0;

    }

    do//ѭ��

    {

        STUDENT * p2 = (STUDENT*)malloc(sizeof(STUDENT));

        fscanf(fp,"%d\t%s\t%f\t%f\t%f\t\n",&p2->number,p2->name,&p2->computer,&p2->maths,&p2->English);

        p1->next = p2;

        p2->next = NULL;

        p1 = p2;

    }while(!feof(fp));

    printf("����������Ҫ�Ĺ������(�����Ŀ)��\n1,�����\n2,����\n3,��Ӣ\n4,�ܷ֣�\n");

    scanf("%d",&function);

    //��������ָ�룬����ѭ��,p3��Ϊͷָ�����һ����Ϊ�˱���,p4�ĸ�ֵ���⣬��Ϊ������p4�ٸ�ֵ

    STUDENT * p4 = NULL;

    STUDENT * p3 = head->next;

    switch(function)

    {

    case 1:

        //��������ٸĽ����㷨

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
    	
    	printf("��������Ч�Ĺ������\n");

        break;


    }

    fclose(fp);

    return head;

}


//һ���ָ���............................................................................
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





//һ���ָ���............................................................................

int save(STUDENT * p)

{

    p=p->next;

    FILE *fp;

    char file_path[200];

    printf("��Ҫ���ļ�����������?(���ļ���������ᴴ��һ�����ļ�,���ļ�\n�ʹ˳���Ľ����Ƿ���ͬһ�ļ����ڣ�����Ѱ��ʱҪ�������·��)\n");

    scanf("%s",file_path);

    //��д����ʽ���ļ�,ע����ļ��ķ�ʽҪ�ʵ���ѡ��

    if((fp = fopen(file_path,"w"))==NULL)

    {

        printf("�޷��򿪴��ļ�����������Ч���ļ���ַ\n");

        return 0;

    }

    while(p!=NULL)


    {

        fprintf(fp,"%d\t%s\t%f\t%f\t%f\t\n",p->number,p->name,p->computer,p->maths,p->English);
        //������д���ļ���fprintf 

        p = p->next;

    }

    fclose(fp);

    return 0;

}






//һ���ָ���............................................................................


void sort_output(STUDENT *head)

{

    //��������

    printf("�����Ľ������\n");

    STUDENT * p = head->next;

    while(p!=NULL)

    {

        printf("%d\t%s\t%f\t%f\t%f\t\n",p->number,p->name,p->computer,p->maths,p->English);

        p=p->next;

    }

}




//һ���ָ���...................................................................................... 
//���ļ��Ľ��飬����ͬһ�ļ����ڣ�����Ҫ�������·�� 
//ѧ������(��������ͳ������,����ֵΪѧ������)
int all_student_number()

{
	
    FILE *pf = fopen("data.txt", "r"); // ���ļ�,����Ĭ������ͬһ�ļ����ڣ���ȷ�����ļ��������ٸ�һ�£���û�� 
    
    char buf[1000];
    
    int lineCnt = 0;
    
    if (!pf) {// �ж��Ƿ�򿪳ɹ�
    
        printf("�޷��򿪴��ļ�����������Ч���ļ���ַ\n");

        return 0;
        
    }
        
    while (fgets(buf, 1000, pf)) // fgetsѭ����ȡ��ֱ���ļ���󣬲Ż᷵��NULL
    
        lineCnt++; // �ۼ�����
        
    fclose(pf);
    
    return lineCnt;
    
}



//һ���ָ���.......................................................................................................... 
//�ܳɼ���ƽ���ɼ� 
float *average_maths1(STUDENT * head){

    STUDENT * p1 = (STUDENT*)malloc(sizeof(STUDENT));

    head = p1;

    FILE *fp;

    char file_path[200];

    printf("������洢ѧ����Ϣ���ļ�����(�������ͬ\nһ�ļ����������ļ����������������·��)\n");

    scanf("%s",file_path);

    if((fp=fopen(file_path,"r"))==NULL)

    {

        printf("�޷��򿪴��ļ�����������Ч���ļ�����\n");

        return 0;

    }
    
    float all_maths,all_computer,all_English,all_grade,all_grade_tempory;//�����grade����s 
    
    float average_maths,average_English,average_computer;
	
	int sum_maths,sum_English,sum_computer,sum_grade;   
	 
    all_maths=all_computer=all_English=all_grade=all_grade_tempory=0;
    
    average_maths=average_English=average_computer=0;
    
    sum_maths=sum_English=sum_computer=sum_grade=0;
  
    
//ѯ���Ƿ���Ҫͳ�Ƹ����������� 
	int w,sum_people,m,E,c,b;
	
	w=sum_people=m=E=c=b=0;
	
    printf("�Ƿ���Ҫͳ��ĳ����������?\n1:��,2:��\n");
    
    scanf("%d",&w);
    
    if(w==1){
    	
    	int a;
    	
    	printf("��Ҫͳ��ʲô��Ŀ?\n1,�����\n2,����\n3,��Ӣ\n0,�˳�����\n");
    	
    	scanf("%d",&a);
    	
    	switch(a){
    		
    		case 0:
    			
    			break;
    			
    		case 1:
    			
    			c=1;
    			
    			printf("������߷�����ͳ�Ƹ÷������µ���\n");
    			
    			scanf("%d",&b);
    			
    			//printf("%d",sum_people_computer);
    			
    			break;
    		
    		case 2:
    			
    			m=1;
    			
    			printf("������߷�����ͳ�Ƹ÷������µ���\n");
    			
    			scanf("%d",&b);
    			
    			//printf("%d",sum_people_maths);
    			
    			break;
    			
    		case 3:
    			
    			E=1;
    			
    			printf("������߷�����ͳ�Ƹ÷������µ���\n");
    			
    			scanf("%d",&b);
    			
    			//printf("%d",sum_people_English);
    			
    			break;
    			
		}
    	
	}
	

    do{
		//�ܳɼ�ģ�� 
        STUDENT * p2 = (STUDENT*)malloc(sizeof(STUDENT));

        fscanf(fp,"%d\t%s\t%f\t%f\t%f\t\n",&p2->number,p2->name,&p2->computer,&p2->maths,&p2->English);
        
        all_maths += p2->maths;
        
		all_computer += p2->computer;
		
		all_English += p2->English;
		
		all_grade += p2->maths+p2->computer+p2->English;
		
		all_grade_tempory = p2->maths+p2->computer+p2->English;
		
		
//ͳ�Ƽ�������...............................................������������ָ�������εĹ��� 
		
		if(p2->maths < 60){
        	
        	sum_maths++;
        	
		}
		
		if(p2->English < 60){
        	
        	sum_English++;
        	
		}
		
		if(p2->computer < 60){
        	
        	sum_computer++;
    	}
    	
    	if(all_grade_tempory < 180){ //���ﲻӦ����all_grade.....................................Ҫ�İ��������������������������������������� 
        	
        	sum_grade++;
    	}
    	
//��һ��ͳ�Ƹ������ε���������,���������if��ѯ���Ƿ���Ҫ�˹��ܣ��ÿռ任ʱ���..................................................................................
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
    
//��������� 
    if (w==1){
    	
    	printf("�÷���֮����%d����\n",sum_people);
    	
	}
    
//�ָ���............. 
    
    int a = all_student_number();//aΪѧ������
    
    average_maths=all_maths/a;
    
    average_computer=all_computer/a;
    
    average_English=all_English/a;
    		
	//ƽ���ɼ��ͺϸ����� 
		
	int function=0; 
		
	printf("����Ҫ�鿴�ĿƳɼ���ƽ���ֺͲ��ϸ�����?(���빦�����)\n");
		
	printf("1,����\n2,�����\n3,��Ӣ\n4,ȫ��\n0,�˳�����\n");
		
	scanf("%d",&function);
		
	switch(function){
			
		case 1:
				
			printf("average_maths=%f\n",all_maths/a);
				
			printf("����������Ϊ%d\n��������Ϊ%d\n",sum_maths,a-sum_maths);
			
			break;
			
		case 2:
				
			printf("average_computer=%f\n",all_computer/a);
				
			printf("����������Ϊ%d\n��������Ϊ%d\n",sum_computer,a-sum_computer);
			
			break;
				
		case 3:
				
			printf("average_English=%f\n",all_English/a);
				
			printf("����������Ϊ%d\n��������Ϊ%d\n",sum_English,a-sum_English);
			
			break;
				
		case 4:
				
			printf("average_grades=%f\n",all_grade/a);
				
			printf("����������Ϊ%d\n��������Ϊ%d\n",sum_grade,a-sum_grade);
			
			break;
				
	}

    fclose(fp);

    return head;

}







 
