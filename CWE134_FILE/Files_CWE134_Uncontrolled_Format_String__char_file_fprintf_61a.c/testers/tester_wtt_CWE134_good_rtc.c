#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE134_Uncontrolled_Format_String/wtt/CWE134_Uncontrolled_Format_String__char_file_fprintf_61a.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C/testcasesupport/io.c"

#define LOGFILE "/tmp/file.txt"
//Mocked functions
//
char __wrap_CWE134_Uncontrolled_Format_String__char_file_fprintf_61b_badSource(char * data){ size_t dataLen = strlen(data);FILE * pFile;if (100-dataLen > 1){pFile = fopen(FILENAME, "r");if (pFile != NULL){if (fgets(data+dataLen, (int)(100-dataLen), pFile) == NULL){printLine("fgets() failed");data[dataLen] = '\0';}fclose(pFile);}}return data; }
char __wrap_CWE134_Uncontrolled_Format_String__char_file_fprintf_61b_goodG2BSource(char * data){ size_t dataLen = strlen(data);FILE * pFile;if (100-dataLen > 1){pFile = fopen(FILENAME, "r");if (pFile != NULL){if (fgets(data+dataLen, (int)(100-dataLen), pFile) == NULL){printLine("fgets() failed");data[dataLen] = '\0';}fclose(pFile);}}return data; }
char __wrap_CWE134_Uncontrolled_Format_String__char_file_fprintf_61b_goodB2GSource(char * data){ size_t dataLen = strlen(data);FILE * pFile;if (100-dataLen > 1){pFile = fopen(FILENAME, "r");if (pFile != NULL){if (fgets(data+dataLen, (int)(100-dataLen), pFile) == NULL){printLine("fgets() failed");data[dataLen] = '\0';}fclose(pFile);}}return data; }


int __wrap_globalReturnsTrueOrFalse() 
{
    //return (rand() % 2);
    return 1;
}

#define CHAR_ARRAY_SIZE 20

char inputBuffer[CHAR_ARRAY_SIZE] = "";

static void test_juliet_rtc(void **state)
{
    (void)state; //unused variable

    char *str = "%xfixedstring";

    char * data;
    char dataBuffer[100] = "";
    data = dataBuffer;

    strcpy(data, str);

    FILE *txtFile;
    txtFile = fopen(LOGFILE, "w");
    if (txtFile != NULL){
        fprintf(txtFile, "%s", str);
        fclose(txtFile);
    }

    char buf[BUFSIZ];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buf);

    goodB2G();
    
    freopen("/dev/tty", "a", stdout);
    
    char *pos;
    if ((pos = strchr(buf, '\n')) != NULL){
        *pos = '\0';
    }
    
    assert_string_equal(buf, str);
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
        cmocka_unit_test(test_juliet_rtc)};

    int count_fail_tests =
        cmocka_run_group_tests(tests, setup, teardown);

    return count_fail_tests;
}