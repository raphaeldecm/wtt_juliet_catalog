#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE369_Divide_by_Zero/wtt/CWE369_Divide_by_Zero__float_fgets_54a.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C/testcasesupport/io.c"

#define CHAR_ARRAY_SIZE 20

char inputBuffer[BUFSIZ];

//Mocked functions
//
void __wrap_CWE369_Divide_by_Zero__float_fgets_54b_badSink(float data){int result = (int)(100.0 / data);printIntLine(result);}
void __wrap_CWE369_Divide_by_Zero__float_fgets_54b_goodG2BSink(float data){if(fabs(data) > 0.000001){int result = (int)(100.0 / data);printIntLine(result);}else{printLine("This would result in a divide by zero");}}
void __wrap_CWE369_Divide_by_Zero__float_fgets_54b_goodB2GSink(float data){if(fabs(data) > 0.000001){int result = (int)(100.0 / data);printIntLine(result);}else{printLine("This would result in a divide by zero");}}

char __wrap_fgets(char *__restrict __s, int __n, FILE *__restrict __stream)
{
    strcpy(__s, inputBuffer);
    return __s;
}

static void test_juliet_rtc(void **state)
{
    (void)state; //unused variable
    float input;
    /* Initialize input */
    input = 0.0F;
    
    sprintf(inputBuffer, "%f", input);

    char buf[BUFSIZ];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buf);

    CWE369_Divide_by_Zero__float_fgets_54_bad();

    freopen("/dev/tty", "a", stdout);

    if (input != 0)
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