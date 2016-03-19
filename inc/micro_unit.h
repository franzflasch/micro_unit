/*
 * micro_unit.h
 *
 *  Created on: Jan 15, 2016
 *      Author: fflasch
 */

#pragma GCC system_header

#ifndef MICRO_UNIT_H_
#define MICRO_UNIT_H_

#include <stdio.h>

/*  Misc. variables */
static int micro_unit_run = 0;
static int micro_unit_assert = 0;
static int micro_unit_fail = 0;
static int micro_unit_fails_within_test = 0;
static int micro_unit_status = 0;

/*  Definitions */
#define MICRO_UNIT_TEST(method_name) static void method_name()
#define MICRO_UNIT_TEST_SUITE(suite_name) static void suite_name()

#define MICRO_UNIT_SAFE_BLOCK(block) do {\
    block\
} while(0)

/*  Run test suite and unset setup and teardown functions */
#define MICRO_UNIT_RUN_SUITE(suite_name) MICRO_UNIT_SAFE_BLOCK(\
    suite_name();\
)

/*  Test runner */
#define MICRO_UNIT_RUN_TEST(test) MICRO_UNIT_SAFE_BLOCK(\
    micro_unit_fails_within_test = micro_unit_fail; \
    printf("\r\nRUNNING Test: %s", #test); \
    test();\
    micro_unit_run++;\
    micro_unit_fails_within_test = micro_unit_fail - micro_unit_fails_within_test; \
    printf("\r\nFINISHED with %d failures\r\n", micro_unit_fails_within_test); \
)

/*  Report */
#define MICRO_UNIT_REPORT() MICRO_UNIT_SAFE_BLOCK(\
    printf("\r\n\%d tests, %d assertions, %d failures\r\n", micro_unit_run, micro_unit_assert, micro_unit_fail);\
)

/*  Assertions */
#define MICRO_UNIT_CHECK(test) MICRO_UNIT_SAFE_BLOCK(\
    micro_unit_assert++;\
    if (!(test)) {\
        micro_unit_fail++; \
        printf("\r\n%s fail: %s", __func__, #test);\
    } \
)

#define MICRO_UNIT_FAIL(message) MICRO_UNIT_SAFE_BLOCK(\
	micro_unit_assert++;\
	micro_unit_fail++; \
	printf("\r\n%s fail: %s", __func__, message);\
	return;\
)

void micro_unit_assert_int_eq(const char *function_name, int expected, int result)
{
    int micro_unit_tmp_e;
    int micro_unit_tmp_r;
    micro_unit_assert++;
    micro_unit_tmp_e = (expected);
    micro_unit_tmp_r = (result);
    if (micro_unit_tmp_e != micro_unit_tmp_r)
    {
        micro_unit_fail++;
        printf("\r\n%s fail: %d expected but was %d", function_name, micro_unit_tmp_e, micro_unit_tmp_r);
    }
}
#define MICRO_UNIT_ASSERT_INT_EQ(expected, result) micro_unit_assert_int_eq(__func__, expected, result)


void micro_unit_assert_double_eq(double expected, double result, double max_diff)
{
    double micro_unit_tmp_e;
    double micro_unit_tmp_r;
    micro_unit_assert++;
    micro_unit_tmp_e = (expected);
    micro_unit_tmp_r = (result);
    if (fabs(micro_unit_tmp_e-micro_unit_tmp_r) > max_diff)
    {
        micro_unit_fail++;
        printf("\r\n%s fail: %g expected but was %g", __func__, micro_unit_tmp_e, micro_unit_tmp_r);
    }
}
#define MICRO_UNIT_ASSERT_DOUBLE_EQ(expected, result) micro_unit_assert_double_eq(__func__, expected, result)

#endif /* MICRO_UNIT_H_ */
