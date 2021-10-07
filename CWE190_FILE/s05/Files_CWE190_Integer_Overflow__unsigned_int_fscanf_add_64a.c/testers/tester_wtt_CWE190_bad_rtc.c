#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE190_Integer_Overflow/wtt/CWE190_Integer_Overflow__unsigned_int_fscanf_add_64a.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcasesupport/io.c"

//Mocked functions
//
void __wrap_CWE190_Integer_Overflow__unsigned_int_fscanf_add_64b_badSink(void * dataVoidPtr){unsigned int * dataPtr = (unsigned int *)dataVoidPtr;unsigned int data = (*dataPtr);unsigned int result = data + 1;printUnsignedLine(result);}
void __wrap_CWE190_Integer_Overflow__unsigned_int_fscanf_add_64b_goodG2BSink(void * dataVoidPtr){unsigned int * dataPtr = (unsigned int *)dataVoidPtr;unsigned int data = (*dataPtr);if (data < UINT_MAX){unsigned int result = data + 1;printUnsignedLine(result);}else{printLine("data value is too large to perform arithmetic safely.");}}
void __wrap_CWE190_Integer_Overflow__unsigned_int_fscanf_add_64b_goodB2GSink(void * dataVoidPtr){unsigned int * dataPtr = (unsigned int *)dataVoidPtr;unsigned int data = (*dataPtr);if (data < UINT_MAX){unsigned int result = data + 1;printUnsignedLine(result);}else{printLine("data value is too large to perform arithmetic safely.");}}


static void test_juliet_rtc(void **state)
{
    (void)state; //unused variable
    unsigned int data;
    data = 3909528228;
    
    char charRes[CHAR_MAX];
    sprintf(charRes, "%u", data + 1);
    
    FILE *inputFile;
    inputFile = fopen("read_rtc.txt", "w");
    if (inputFile != NULL){
        fprintf(inputFile, "%u\n", data);
        fclose(inputFile);
    }

    char buf[BUFSIZ];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buf);

    freopen("read_rtc.txt", "r", stdin); // change the behaviour of standard input to read from a file.
    
    CWE190_Integer_Overflow__unsigned_int_fscanf_add_64_bad();

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