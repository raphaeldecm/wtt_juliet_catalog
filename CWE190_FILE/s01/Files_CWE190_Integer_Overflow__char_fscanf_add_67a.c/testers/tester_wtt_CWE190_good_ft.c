#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE190_Integer_Overflow/wtt/CWE190_Integer_Overflow__char_fscanf_add_67a.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcasesupport/io.c"

#define CHAR_ARRAY_SIZE 20

int inputBuffer;

//Mocked functions
//
void __wrap_CWE190_Integer_Overflow__char_fscanf_add_67b_badSink(CWE190_Integer_Overflow__char_fscanf_add_67_structType myStruct){char data = myStruct.structFirst;char result = data + 1;printHexCharLine(result);}
void __wrap_CWE190_Integer_Overflow__char_fscanf_add_67b_goodG2BSink(CWE190_Integer_Overflow__char_fscanf_add_67_structType myStruct){char data = myStruct.structFirst;if (data < CHAR_MAX){char result = data + 1;printHexCharLine(result);}else{printLine("data value is too large to perform arithmetic safely.");}}
void __wrap_CWE190_Integer_Overflow__char_fscanf_add_67b_goodB2GSink(CWE190_Integer_Overflow__char_fscanf_add_67_structType myStruct){char data = myStruct.structFirst;if (data < CHAR_MAX){char result = data + 1;printHexCharLine(result);}else{printLine("data value is too large to perform arithmetic safely.");}}


static void test_juliet_rtc(void **state)
{
    (void)state; //unused variable

    char data;
    data = ' ';
    scanf("%c\n", &data);
    
    char charHex[CHAR_MAX + 1];
    sprintf(charHex, "%02x", data + 1);

    FILE *inputFile;
    inputFile = fopen("read_ft.txt", "w");
    if (inputFile != NULL){
        fprintf(inputFile, "%c\n", data);
        fclose(inputFile);
    }

    FILE *fileAddress;
    fileAddress = fopen("log_afl_good.txt", "a");
    if (fileAddress != NULL){
        fprintf(fileAddress, "%c\n", data);
        fclose(fileAddress);
    }

    char buf[BUFSIZ];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buf);
    
    freopen("read_ft.txt", "r", stdin);

    goodB2G();

    freopen("/dev/tty", "a", stdout);

    char *pos;
    if ((pos = strchr(buf, '\n')) != NULL)
    {
        *pos = '\0';
    }
    if(strcmp(buf, "data value is too large to perform arithmetic safely.") == 0){
        assert_string_equal(buf, "data value is too large to perform arithmetic safely.");
    } else {
        assert_string_equal(buf, charHex);
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