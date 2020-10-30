#ifndef HEADER_FILE
#define HEADER_FILE
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int sendEmail(char* contentEmail, char* mail_receive)
{
	char cmd[100];  // to hold the command.
    // char to[] = "sample@example.com"; // email id of the recepient.
    // char body[] = "SO rocks";    // email body.
    char tempFile[100];     // name of tempfile.

    strcpy(tempFile,tempnam("/tmp","sendmail")); // generate temp file name.

    FILE *fp = fopen(tempFile,"w"); // open it for writing.
    fprintf(fp,"%s\n",contentEmail);        // write body to it.
    fclose(fp);             // close it.

    sprintf(cmd,"sendmail %s < %s",mail_receive,tempFile); // prepare command.
    system(cmd);     // execute it.

    return 0;
}