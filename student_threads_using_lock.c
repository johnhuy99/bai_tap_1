#include"sendmail.h"
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>


// Declare and define the struct student
struct student
{
	
	char* name;
	double gpa;
	double tuition_fee;
	int toeic;
	int credits;
	char* email;	
};

// Declare and initial a variable of struct student
struct student my_student = {"Dao Xuan Phung",0,0,0,0,"phungdaoxuanbkhn@gmail.com"};

// select the infos need to update
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

// Declare mutex
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *update_info_student(void* ptr);
//void *send_mail(void* ptr);
int main()
{
	// declare 2 ids of threads
	pthread_t id_thread_1,id_thread_2;
	// message
	char* msg1 = "first thread started";
	char* msg2 = "second thread started";

	// create 2 threads

	pthread_create(&id_thread_1, NULL, update_info_student,(void*)msg1);
	pthread_create(&id_thread_2, NULL, update_info_student,(void*)msg2);


	// wait for threads to finish
	pthread_join(id_thread_1, NULL);
	pthread_join(id_thread_2, NULL);

	return 0;
}



void *update_info_student(void* ptr)
{
	// start critical section
	pthread_mutex_lock(&lock);

	char*msg = (char*) ptr;

	char content_mail[] = "Thong tin cua ban da duoc update:\n";
	char temp_gpa[50];
	char temp_toeic[50];
	char temp_credits[50];
	char temp_tuition[50];
	char temp_name[50];
	char temp_id_thread[50];
	

	//print message pass into the function
	printf("\nmsg: %s\n",msg);
	//print the id of the thread that in the execution
	printf("id: %ld\n",pthread_self());
	
	menu();

	// Show info student after updated
	printf("\n-----Thong tin sinh vien-----\n");
	printf("Ho va ten: %s\n",my_student.name);
	printf("Diem gpa: %0.2f\n",my_student.gpa);
	printf("Diem TOEIC gan nhat: %d\n",my_student.toeic);
	printf("So tin chi dat duoc: %d\n",my_student.credits);
	printf("No hoc phi: %0.1f\n",my_student.tuition_fee);

	printf("Updated successfully\n\n");


	// Send a email for the student
	sprintf(temp_id_thread, "ID THREAD:%ld\n",pthread_self());
	sprintf(temp_gpa, "GPA: %0.2f \n", my_student.gpa);
	sprintf(temp_toeic, "TOEIC:%d \n", my_student.toeic);
	sprintf(temp_credits, "CREDITS:%d \n", my_student.credits);
	sprintf(temp_name, "NAME:%s \n", my_student.name);
	sprintf(temp_tuition, "TUITION FEE:%0.2lf \n", my_student.tuition_fee);

	strcat(content_mail, temp_gpa);
	strcat(content_mail, temp_name);
	strcat(content_mail, temp_toeic);
	strcat(content_mail, temp_credits);
	strcat(content_mail, temp_tuition);
	strcat(content_mail, temp_id_thread);

	sendEmail(content_mail,my_student.email);

	printf("\nSent mail successfully!!!\n\n");


	// end the critical section
	pthread_mutex_unlock(&lock);

	pthread_exit(NULL);
}