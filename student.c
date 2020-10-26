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
};

// Declare and initial a variable of struct student
struct student my_student = {"Dao Xuan Phung",0,0,0,0};

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
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *update_info_student(void* ptr);
void *show_info_student(void* ptr);

int main()
{
	pthread_t id_thread_1,id_thread_2,id_thread_3;
	char* msg1 = "first thread";
	char* msg2 = "second thread";
	char* msg3 = "third thread";


	pthread_create(&id_thread_1, NULL, update_info_student,(void*)msg1);
	pthread_create(&id_thread_2, NULL, update_info_student,(void*)msg2);
	pthread_create(&id_thread_3, NULL, update_info_student,(void*)msg3);


	// wait for threads to finish
	pthread_join(id_thread_1, NULL);
	pthread_join(id_thread_2, NULL);
	pthread_join(id_thread_3, NULL);

	return 0;
}



void *update_info_student(void* ptr)
{
	// start critical section
	pthread_mutex_lock(&mutex);

	char*msg = (char*) ptr;
	

	menu();
	printf("\nmsg: %s\n",msg);
	printf("id: %ld\n",pthread_self());

	// Show info student after updated
	printf("\n-----Thong tin sinh vien-----\n");
	printf("Ho va ten: %s\n",my_student.name);
	printf("Diem gpa: %0.2f\n",my_student.gpa);
	printf("Diem TOEIC gan nhat: %d\n",my_student.toeic);
	printf("So tin chi dat duoc: %d\n",my_student.credits);
	printf("No hoc phi: %0.1f\n",my_student.tuition_fee);

	
	printf("Updated successfully\n\n\n");

	// end the critical section
	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}

