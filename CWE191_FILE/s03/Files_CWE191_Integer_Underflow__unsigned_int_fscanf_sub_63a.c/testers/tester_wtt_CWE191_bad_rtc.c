#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE191_Integer_Underflow/wtt/CWE191_Integer_Underflow__unsigned_int_fscanf_sub_63a.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcasesupport/io.c"

//Mocked functions
//
void __wrap_CWE191_Integer_Underflow__unsigned_int_fscanf_sub_63b_badSink(unsigned int * dataPtr){unsigned int data = *dataPtr;unsigned int result = data - 1;printUnsignedLine(result);}
void __wrap_CWE191_Integer_Underflow__unsigned_int_fscanf_sub_63b_goodG2BSink(unsigned int * data){unsigned int dataPtr = *data;if (dataPtr > 0){unsigned int result = dataPtr - 1;printUnsignedLine(result);}else{printLine("data value is too large to perform subtraction.");}}
void __wrap_CWE191_Integer_Underflow__unsigned_int_fscanf_sub_63b_goodB2GSink(unsigned int * data){unsigned int dataPtr = *data;if (dataPtr > 0){unsigned int result = dataPtr - 1;printUnsignedLine(result);}else{printLine("data value is too large to perform subtraction.");}}


#define CHAR_ARRAY_SIZE 20

char resBuffer[CHAR_ARRAY_SIZE] = "";

static void test_juliet_rtc(void **state)
{
    (void)state; //unused variable
    unsigned int data;
    data = 0;

    unsigned int result = data - 1;
    sprintf(resBuffer, "%u", result);
    
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
    
    CWE191_Integer_Underflow__unsigned_int_fscanf_sub_63_bad();

    freopen("/dev/tty", "a", stdout);
    
    char *pos;
    if ((pos = strchr(buf, '\n')) != NULL)
    {
        *pos = '\0';
    }
    
    if(strcmp(buf, "data value is too large to perform subtraction.") == 0){
        assert_string_equal(buf, "data value is too large to perform subtraction.");
    } else if(data > 0){
        assert_string_equal(buf, resBuffer);
    } else if(data == 0){
        assert_true(atoi(buf) == 0);
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