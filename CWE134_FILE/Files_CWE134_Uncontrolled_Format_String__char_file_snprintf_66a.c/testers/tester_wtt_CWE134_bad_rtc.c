#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE134_Uncontrolled_Format_String/wtt/CWE134_Uncontrolled_Format_String__char_file_snprintf_66a.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C/testcasesupport/io.c"

#define LOGFILE "/tmp/file.txt"
#define SNPRINTF snprintf
//Mocked functions
//
void __wrap_CWE134_Uncontrolled_Format_String__char_file_snprintf_66b_badSink(char * dataArray[]){char * data = dataArray[2]; char dest[100] = "";SNPRINTF(dest, 100-1, data);printLine(dest); }
void __wrap_CWE134_Uncontrolled_Format_String__char_file_snprintf_66b_goodG2BSink(char * dataArray[]){char * data = dataArray[2]; char dest[100] = "";SNPRINTF(dest, 100-1, "%s", data);printLine(dest); }
void __wrap_CWE134_Uncontrolled_Format_String__char_file_snprintf_66b_goodB2GSink(char * dataArray[]){char * data = dataArray[2]; char dest[100] = "";SNPRINTF(dest, 100-1, "%s", data);printLine(dest); }


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

    CWE134_Uncontrolled_Format_String__char_file_snprintf_66_bad();
    
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