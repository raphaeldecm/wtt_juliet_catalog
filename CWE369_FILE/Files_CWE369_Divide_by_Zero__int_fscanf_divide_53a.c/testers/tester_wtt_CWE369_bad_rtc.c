#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE369_Divide_by_Zero/wtt/CWE369_Divide_by_Zero__int_fscanf_divide_53a.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcasesupport/io.c"

#define CHAR_ARRAY_SIZE 20

char inputBuffer[BUFSIZ];

//Mocked functions
//
void __wrap_CWE369_Divide_by_Zero__int_fscanf_divide_53b_badSink(int data){int result = (int)(100.0 / data);printIntLine(result);}
void __wrap_CWE369_Divide_by_Zero__int_fscanf_divide_53b_goodG2BSink(int data){if(fabs(data) > 0.000001){int result = (int)(100.0 / data);printIntLine(result);}else{printLine("This would result in a divide by zero");}}
void __wrap_CWE369_Divide_by_Zero__int_fscanf_divide_53b_goodB2GSink(int data){if(fabs(data) > 0.000001){int result = (int)(100.0 / data);printIntLine(result);}else{printLine("This would result in a divide by zero");}}


static void test_juliet_rtc(void **state)
{
    (void)state; //unused variable
    int data;
    /* Initialize Data */
    data = 0;
    
    FILE *inputFile;
    inputFile = fopen("read_rtc.txt", "w");
    if (inputFile != NULL){
        fprintf(inputFile, "%d\n", data);
        fclose(inputFile);
    }

    char buf[BUFSIZ];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buf);

    freopen("read_rtc.txt", "r", stdin); // change the behaviour of standard input to read from a file.
    
    CWE369_Divide_by_Zero__int_fscanf_divide_53_bad();

    freopen("/dev/tty", "a", stdout);

    if (data != 0)
    {
        assert_true(1);
    }
    else
    {
        char *pos;
        if ((pos = strchr(buf, '\n')) != NULL)
        {
            *pos = '\0';
        }
        assert_string_equal(buf ,"This would result in a divide by zero");
    }

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