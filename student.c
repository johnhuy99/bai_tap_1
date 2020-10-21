#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>


// Tao struct thong tin cho sinh vien
struct student
{
	char* name;
	double gpa;
	double tuition_fee;
	int toeic;
	int credits;	
};

// Khoi tao bien 
struct student my_student = {"Dao Xuan Phung",0,0,0,0};

// Chon thong tin can update
void menu()
{
	int n;
	do
	{
		printf("----Select what you want to update by number----\n");
		printf("1.GPA\n");
		printf("2.Tuition_fee\n");
		printf("3.TOEIC\n");
		printf("4.Credits\n");
		printf("5.Exit\n");
		scanf("%d",&n);
		switch(n)
		{
			case 1:
			    printf("Enter gpa:\n"); scanf("%lf",&my_student.gpa);
			    break;

			case 2:
			    printf("Enter tuition_fee:\n"); scanf("%lf",&my_student.tuition_fee);
			    break;
			case 3:
			    printf("Enter toeic:\n"); scanf("%d",&my_student.toeic);
			    break;
			case 4:
			    printf("Enter credits:\n"); scanf("%d",&my_student.credits);
			    break;
			default:
			    break;            
		}
	}while(n<5);	
}

// Khai bao lock de khoa thread
pthread_mutex_t lock;


void *update_info_student(void* ptr);
void *show_info_student(void* ptr);

int main()
{
	pthread_t thread_1,thread_2;
	int thret1,thret2;
	char* msg1 = "first thread";
	char* msg2 = "second thread";
	thret1 = pthread_create(&thread_1, NULL, update_info_student, (void*) msg1);
	thret2 = pthread_create(&thread_2, NULL, show_info_student, (void*) msg2);
	pthread_mutex_lock(&lock);
	printf("\nid thread 1 : %ld\n",thread_1);
	printf("id thread 2 : %ld\n",thread_2);
	pthread_mutex_unlock(&lock);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

	return 0;
}

void *update_info_student(void* ptr)
{
	pthread_mutex_lock(&lock);
	char*msg = (char*) ptr;
	printf("\nmsg: %s\n",msg);
	printf("id: %ld\n",pthread_self());
	menu();
	printf("Updated successfully\n");
	pthread_mutex_unlock(&lock);
}

void *show_info_student(void* ptr)
{
	pthread_mutex_lock(&lock);
	char* msg = (char*) ptr;
	printf("\nmsg: %s\n",msg);
	printf("id: %ld\n",pthread_self());
	printf("-----Thong tin sinh vien-----\n");
	printf("Ho va ten: %s\n",my_student.name);
	printf("Diem gpa: %0.2f\n",my_student.gpa);
	printf("Diem TOEIC gan nhat: %d\n",my_student.toeic);
	printf("So tin chi dat duoc: %d\n",my_student.credits);
	printf("No hoc phi: %0.1f\n",my_student.tuition_fee);
	pthread_mutex_unlock(&lock);
}