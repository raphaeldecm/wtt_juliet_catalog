#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE190_Integer_Overflow/wtt/CWE190_Integer_Overflow__unsigned_int_fscanf_multiply_64a.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcasesupport/io.c"

#define CHAR_ARRAY_SIZE 20

int inputBuffer;

//Mocked functions
//
void __wrap_CWE190_Integer_Overflow__unsigned_int_fscanf_multiply_64b_badSink(void * dataVoidPtr){unsigned int * dataPtr = (unsigned int *)dataVoidPtr;unsigned int data = (*dataPtr);unsigned int result = data * 2;printUnsignedLine(result);}
void __wrap_CWE190_Integer_Overflow__unsigned_int_fscanf_multiply_64b_goodG2BSink(void * dataVoidPtr){unsigned int * dataPtr = (unsigned int *)dataVoidPtr;unsigned int data = (*dataPtr);if (data < UINT_MAX/2){unsigned int result = data * 2;printUnsignedLine(result);}else{printLine("data value is too large to perform arithmetic safely.");}}
void __wrap_CWE190_Integer_Overflow__unsigned_int_fscanf_multiply_64b_goodB2GSink(void * dataVoidPtr){unsigned int * dataPtr = (unsigned int *)dataVoidPtr;unsigned int data = (*dataPtr);if (data < UINT_MAX/2){unsigned int result = data * 2;printUnsignedLine(result);}else{printLine("data value is too large to perform arithmetic safely.");}}


static void test_juliet_rtc(void **state)
{
    (void)state; //unused variable

    unsigned int data;
    data = 0;
    scanf("%u\n", &data);
    
    char charRes[CHAR_MAX + 1];
    sprintf(charRes, "%u", data * 2);

    FILE *inputFile;
    inputFile = fopen("read_ft.txt", "w");
    if (inputFile != NULL){
        fprintf(inputFile, "%u\n", data);
        fclose(inputFile);
    }

    FILE *fileAddress;
    fileAddress = fopen("log_afl_bad.txt", "a");
    if (fileAddress != NULL){
        fprintf(fileAddress, "%u\n", data);
        fclose(fileAddress);
    }

    char buf[BUFSIZ];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buf);
    
    freopen("read_ft.txt", "r", stdin);
    
    CWE190_Integer_Overflow__unsigned_int_fscanf_multiply_64_bad();

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