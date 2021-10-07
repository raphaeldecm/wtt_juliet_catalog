#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE190_Integer_Overflow/wtt/CWE190_Integer_Overflow__short_fscanf_add_54c.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcasesupport/io.c"

#define CHAR_ARRAY_SIZE 20

int inputBuffer;

//Mocked functions
//
void __wrap_CWE190_Integer_Overflow__short_fscanf_add_54d_badSink(short data){short result = data + 1;printIntLine(result);}
void __wrap_CWE190_Integer_Overflow__short_fscanf_add_54d_goodG2BSink(short data){if (data < SHRT_MAX){int result = data + 1;printIntLine(result);}else{printLine("data value is too large to perform arithmetic safely.");}}
void __wrap_CWE190_Integer_Overflow__short_fscanf_add_54d_goodB2GSink(short data){if (data < SHRT_MAX){int result = data + 1;printIntLine(result);}else{printLine("data value is too large to perform arithmetic safely.");}}


static void test_juliet_rtc(void **state)
{
    (void)state; //unused variable

    short data;
    data = 0;
    scanf("%hd\n", &data);
    
    char charRes[CHAR_MAX + 1];
    sprintf(charRes, "%hd", data + 1);

    FILE *inputFile;
    inputFile = fopen("read_ft.txt", "w");
    if (inputFile != NULL){
        fprintf(inputFile, "%hd\n", data);
        fclose(inputFile);
    }

    FILE *fileAddress;
    fileAddress = fopen("log_afl_bad.txt", "a");
    if (fileAddress != NULL){
        fprintf(fileAddress, "%hd\n", data);
        fclose(fileAddress);
    }

    char buf[BUFSIZ];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buf);
    
    freopen("read_ft.txt", "r", stdin);
    
    CWE190_Integer_Overflow__short_fscanf_add_54c_badSink(data);//();

    freopen("/dev/tty", "a", stdout);

    char *pos;
    if ((pos = strchr(buf, '\n')) != NULL)
    {
        *pos = '\0';
    }
    if(strcmp(buf, "data value is too large to perform arithmetic safely.") == 0){
        assert_string_equal(buf, "data value is too large to perform arithmetic safely.");
    } else if(data > 0) {
        assert_true(atoi(buf) >= 0);
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