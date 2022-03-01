#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE122_Heap_Based_Buffer_Overflow/wtt/CWE122_Heap_Based_Buffer_Overflow__c_CWE129_fgets_51a.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcasesupport/io.c"

//Mocked functions
//
void __wrap_CWE122_Heap_Based_Buffer_Overflow__c_CWE129_fgets_51b_badSink(int data){ int i;int * buffer = (int *)malloc(10 * sizeof(int));for (i = 0; i < 10; i++){buffer[i] = 0;}if (data >= 0){buffer[data] = 1;for(i = 0; i < 10; i++){printIntLine(buffer[i]);}}else{printLine("ERROR: Array index is negative.");}free(buffer); }
void __wrap_CWE122_Heap_Based_Buffer_Overflow__c_CWE129_fgets_51b_goodG2BSink(int data){ int i;int * buffer = (int *)malloc(10 * sizeof(int));for (i = 0; i < 10; i++){buffer[i] = 0;}if (data >= 0 && data < (10)){buffer[data] = 1;for(i = 0; i < 10; i++){printIntLine(buffer[i]);}}else{printLine("ERROR: Array index is out-of-bounds");}free(buffer); }
void __wrap_CWE122_Heap_Based_Buffer_Overflow__c_CWE129_fgets_51b_goodB2GSink(int data){ int i;int * buffer = (int *)malloc(10 * sizeof(int));for (i = 0; i < 10; i++){buffer[i] = 0;}if (data >= 0 && data < (10)){buffer[data] = 1;for(i = 0; i < 10; i++){printIntLine(buffer[i]);}}else{printLine("ERROR: Array index is out-of-bounds");}free(buffer); }


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
    data = 0;

    scanf("%d\n", &data);

    sprintf(inputBuffer, "%d", data);

    FILE *fileAddress;
    fileAddress = fopen("log_afl_bad.txt", "a");
    if (fileAddress != NULL){
        fprintf(fileAddress, "%d\n", data);
        fclose(fileAddress);
    }

    char buf[BUFSIZ];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buf);
    
    CWE122_Heap_Based_Buffer_Overflow__c_CWE129_fgets_51_bad();

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