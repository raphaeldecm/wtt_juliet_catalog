#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE369_Divide_by_Zero/wtt/CWE369_Divide_by_Zero__float_fgets_11.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C/testcasesupport/io.c"

#define CHAR_ARRAY_SIZE 20

char inputBuffer[BUFSIZ];

//Mocked functions
//
//
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
    scanf("%f\n", &input);
    
    sprintf(inputBuffer, "%f", input);

    FILE *fileAddress;
    fileAddress = fopen("log_afl_good.txt", "a");
    if (fileAddress != NULL){
        fprintf(fileAddress, "%f\n", input);
        fclose(fileAddress);
    }

    char buf[BUFSIZ];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buf);

    goodB2G1();

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