#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE134_Uncontrolled_Format_String/wtt/CWE134_Uncontrolled_Format_String__char_file_printf_63a.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C/testcasesupport/io.c"

#define LOGFILE "/tmp/file.txt"
//Mocked functions
//
void __wrap_CWE134_Uncontrolled_Format_String__char_file_printf_63b_badSink(char * * dataPtr){char * data = *dataPtr; printf(data); }
void __wrap_CWE134_Uncontrolled_Format_String__char_file_printf_63b_goodG2BSink(char * * data){char * dataPtr = *data; printf("%s\n", dataPtr); }
void __wrap_CWE134_Uncontrolled_Format_String__char_file_printf_63b_goodB2GSink(char * * data){char * dataPtr = *data; printf("%s\n", dataPtr); }


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