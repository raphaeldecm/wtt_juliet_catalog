#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE134_Uncontrolled_Format_String/wtt/CWE134_Uncontrolled_Format_String__char_file_fprintf_54a.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C/testcasesupport/io.c"

#define LOGFILE "/tmp/file.txt"
//Mocked functions
//
void __wrap_CWE134_Uncontrolled_Format_String__char_file_fprintf_54b_badSink(char * data){ fprintf(stdout, data); }
void __wrap_CWE134_Uncontrolled_Format_String__char_file_fprintf_54b_goodG2BSink(char * data){ fprintf(stdout, "%s\n", data); }
void __wrap_CWE134_Uncontrolled_Format_String__char_file_fprintf_54b_goodB2GSink(char * data){ fprintf(stdout, "%s\n", data); }


int __wrap_globalReturnsTrueOrFalse() 
{
    //return (rand() % 2);
    return 1;
}

#define CHAR_ARRAY_SIZE 20

char inputBuffer[CHAR_ARRAY_SIZE] = "";

static void test_juliet_ft(void **state)
{
    (void)state; //unused variable

    char data[100] = "";
    
    scanf("%s\n", &data);

    char * str;
    char strBuffer[100] = "";
    str = strBuffer;

    strcpy(str, data);


    FILE *txtFile;
    txtFile = fopen(LOGFILE, "w");
    if (txtFile != NULL){
        fprintf(txtFile, "%s", data);
        fclose(txtFile);
    }

    FILE *fileAddress;
    fileAddress = fopen("log_afl_bad.txt", "a");
    if (fileAddress != NULL){
        fprintf(fileAddress, "%s\n", data);
        fclose(fileAddress);
    }

    char buf[BUFSIZ];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buf);

    CWE134_Uncontrolled_Format_String__char_file_fprintf_54_bad();
    
    freopen("/dev/tty", "a", stdout);
    
    char *pos;
    if ((pos = strchr(buf, '\n')) != NULL){
        *pos = '\0';
    }
    
    assert_string_equal(buf, data);
}

int setup(void **state){
    return 0;
}

int teardown(void **state){
    return 0;
}

int main(int argc, char **argv)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_juliet_ft)};

    int count_fail_tests =
        cmocka_run_group_tests(tests, setup, teardown);

    return count_fail_tests;
}