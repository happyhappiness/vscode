
#include "hiredis.h"

/* The following lines make up our testing "framework" :) */
static int tests = 0, fails = 0;
#define test(_s) { printf("#%02d ", ++tests); printf(_s); }
#define test_cond(_c) if(_c) printf("PASSED\n"); else {printf("FAILED\n"); fails++;}

static long long usec(void) {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000000)+tv.tv_usec;
}

static int use_unix = 0;
static redisContext *blocking_context = NULL;
static void __connect(redisContext **target) {
    *target = blocking_context = (use_unix ?
        redisConnectUnix("/tmp/redis.sock") : redisConnect((char*)"127.0.0.1", 6379));
    if (blocking_context->err) {
        printf("Connection error: %s\n", blocking_context->errstr);
        exit(1);
    }
}

static void test_format_commands(void) {
