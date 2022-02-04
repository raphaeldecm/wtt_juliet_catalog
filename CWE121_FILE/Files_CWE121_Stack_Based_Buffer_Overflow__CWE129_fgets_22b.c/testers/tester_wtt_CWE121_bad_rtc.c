#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE121_Stack_Based_Buffer_Overflow/wtt/CWE121_Stack_Based_Buffer_Overflow__CWE129_fgets_22b.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcasesupport/io.c"

//Mocked functions
int CWE121_Stack_Based_Buffer_Overflow__CWE129_fgets_22_badGlobal = 1;
int CWE121_Stack_Based_Buffer_Overflow__CWE129_fgets_22_goodB2G1Global = 0;
int CWE121_Stack_Based_Buffer_Overflow__CWE129_fgets_22_goodB2G2Global = 0;
int CWE121_Stack_Based_Buffer_Overflow__CWE129_fgets_22_goodG2BGlobal = 0;

//

#define CHAR_ARRAY_SIZE 20

char inputBuffer[CHAR_ARRAY_SIZE] = "";

char __wrap_fgets(char *__restrict __s, int __n, FILE *__restrict __stream)
{
    strcpy(__s, inputBuffer);
    return __s;
}

static void test_juliet_rtc(void **state)
{
    (void)state; //unused variable
    int data;
    data = 10000;

    sprintf(inputBuffer, "%d", data);
    
    char buf[BUFSIZ];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buf);
    
    CWE121_Stack_Based_Buffer_Overflow__CWE129_fgets_22_badSink(data);//();

    freopen("/dev/tty", "a", stdout);
    
    char *pos;
    if ((pos = strchr(buf, '\n')) != NULL)
    {
        *pos = '\0';
    }


    assert_true(1);

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