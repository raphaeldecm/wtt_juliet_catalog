#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcases/CWE190_Integer_Overflow/wtt/CWE190_Integer_Overflow__int64_t_fscanf_square_22b.c"
#include "/home/raphael/DOCFILES/DoctoralFiles/Juliet/C1.2/testcasesupport/io.c"

//Mocked functions
int CWE190_Integer_Overflow__int64_t_fscanf_square_22_badGlobal = 1;
int CWE190_Integer_Overflow__int64_t_fscanf_square_22_goodB2G1Global = 0;
int CWE190_Integer_Overflow__int64_t_fscanf_square_22_goodB2G2Global = 0;
int CWE190_Integer_Overflow__int64_t_fscanf_square_22_goodG2BGlobal = 0;

//

static void test_juliet_rtc(void **state)
{
    (void)state; //unused variable
    int64_t data;
    data = 214147487;
    int64_t result = data * data;
    
    char charRes[CHAR_MAX];
    sprintf(charRes, "%lld", result);
    
    FILE *inputFile;
    inputFile = fopen("read_rtc.txt", "w");
    if (inputFile != NULL){
        fprintf(inputFile, "%lld\n", data);
        fclose(inputFile);
    }

    char buf[BUFSIZ];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buf);

    freopen("read_rtc.txt", "r", stdin); // change the behaviour of standard input to read from a file.
    
    CWE190_Integer_Overflow__int64_t_fscanf_square_22_goodB2G1Sink(data);//();

    freopen("/dev/tty", "a", stdout);
    
    char *pos;
    if ((pos = strchr(buf, '\n')) != NULL)
    {
        *pos = '\0';
    }
    if(strcmp(buf, "data value is too large to perform arithmetic safely.") == 0){
        assert_string_equal(buf, "data value is too large to perform arithmetic safely.");
    } else {
        assert_string_equal(buf, charRes);
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