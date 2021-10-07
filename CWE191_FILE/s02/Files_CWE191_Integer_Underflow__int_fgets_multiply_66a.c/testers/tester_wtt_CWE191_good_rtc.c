#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE191_Integer_Underflow/wtt/CWE191_Integer_Underflow__int_fgets_multiply_66a.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcasesupport/io.c"

//Mocked functions
//
void __wrap_CWE191_Integer_Underflow__int_fgets_multiply_66b_badSink(int dataArray[]){int data = dataArray[2];int result = data * 2;printIntLine(result);}
void __wrap_CWE191_Integer_Underflow__int_fgets_multiply_66b_goodG2BSink(int dataArray[]){int data = dataArray[2];if (data > (INT_MIN/2)){int result = data * 2;printIntLine(result);}else{printLine("data value is too small to perform multiplication.");}}
void __wrap_CWE191_Integer_Underflow__int_fgets_multiply_66b_goodB2GSink(int dataArray[]){int data = dataArray[2];if (data > (INT_MIN/2)){int result = data * 2;printIntLine(result);}else{printLine("data value is too small to perform multiplication.");}}


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
    data = INT_MIN;
    int result = data * 2;

    sprintf(inputBuffer, "%d", data);

    char buf[BUFSIZ];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buf);
    int dataArray[5];
dataArray[2] = data;
    goodB2G();

    freopen("/dev/tty", "a", stdout);
    
    char *pos;
    if ((pos = strchr(buf, '\n')) != NULL)
    {
        *pos = '\0';
    }
    
    if(strcmp(buf, "data value is too small to perform multiplication.") == 0){
        assert_string_equal(buf, "data value is too small to perform multiplication.");
    } else if(data < 0){
        assert_true(atoi(buf) < 0);
    } else {
        assert_true(1);
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