#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE191_Integer_Underflow/wtt/CWE191_Integer_Underflow__int_fscanf_sub_66a.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcasesupport/io.c"

#define CHAR_ARRAY_SIZE 20

int inputBuffer;

//Mocked functions
//
void __wrap_CWE191_Integer_Underflow__int_fscanf_sub_66b_badSink(int dataArray[]){int data = dataArray[2];int result = data - 1;printIntLine(result);}
void __wrap_CWE191_Integer_Underflow__int_fscanf_sub_66b_goodG2BSink(int dataArray[]){int data = dataArray[2];if (data > (INT_MIN/2)){int result = data - 1;printIntLine(result);}else{printLine("data value is too large to perform subtraction.");}}
void __wrap_CWE191_Integer_Underflow__int_fscanf_sub_66b_goodB2GSink(int dataArray[]){int data = dataArray[2];if (data > (INT_MIN/2)){int result = data - 1;printIntLine(result);}else{printLine("data value is too large to perform subtraction.");}}


static void test_juliet_rtc(void **state)
{
    (void)state; //unused variable
    
    int data;
    data = 0;
    scanf("%d\n", &data);
    
    int result = data - 1;

    FILE *inputFile;
    inputFile = fopen("read_ft.txt", "w");
    if (inputFile != NULL){
        fprintf(inputFile, "%d\n", data);
        fclose(inputFile);
    }

    FILE *fileAddress;
    fileAddress = fopen("log_afl_good.txt", "a");
    if (fileAddress != NULL){
        fprintf(fileAddress, "%d\n", data);
        fclose(fileAddress);
    }

    char buf[BUFSIZ];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buf);
    
    freopen("read_ft.txt", "r", stdin);
int dataArray[5];
dataArray[2] = data;
    goodB2G();

    freopen("/dev/tty", "a", stdout);

    char *pos;
    if ((pos = strchr(buf, '\n')) != NULL)
    {
        *pos = '\0';
    }
    if(strcmp(buf, "data value is too large to perform subtraction.") == 0){
        assert_string_equal(buf, "data value is too large to perform subtraction.");
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