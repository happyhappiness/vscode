int main(void) {
    {
        struct sdshdr *sh;
        sds x = sdsnew("foo"), y;

        test_cond("Create a string and obtain the length",
            sdslen(x) == 3 && memcmp(x,"foo\0",4) == 0)

        sdsfree(x);
        x = sdsnewlen("foo",2);
        test_cond("Create a string with specified length",
            sdslen(x) == 2 && memcmp(x,"fo\0",3) == 0)

        x = sdscat(x,"bar");
        test_cond("Strings concatenation",
            sdslen(x) == 5 && memcmp(x,"fobar\0",6) == 0);

        x = sdscpy(x,"a");
        test_cond("sdscpy() against an originally longer string",
            sdslen(x) == 1 && memcmp(x,"a\0",2) == 0)

        x = sdscpy(x,"xyzxxxxxxxxxxyyyyyyyyyykkkkkkkkkk");
        test_cond("sdscpy() against an originally shorter string",
            sdslen(x) == 33 &&
            memcmp(x,"xyzxxxxxxxxxxyyyyyyyyyykkkkkkkkkk\0",33) == 0)

        sdsfree(x);
        x = sdscatprintf(sdsempty(),"%d",123);
        test_cond("sdscatprintf() seems working in the base case",
            sdslen(x) == 3 && memcmp(x,"123\0",4) == 0)

        sdsfree(x);
        x = sdsnew("--");
        x = sdscatfmt(x, "Hello %s World %I,%I--", "Hi!", LLONG_MIN,LLONG_MAX);
        test_cond("sdscatfmt() seems working in the base case",
            sdslen(x) == 60 &&
            memcmp(x,"--Hello Hi! World -9223372036854775808,"
                     "9223372036854775807--",60) == 0)

        sdsfree(x);
        x = sdsnew("--");
        x = sdscatfmt(x, "%u,%U--", UINT_MAX, ULLONG_MAX);
        test_cond("sdscatfmt() seems working with unsigned numbers",
            sdslen(x) == 35 &&
            memcmp(x,"--4294967295,18446744073709551615--",35) == 0)

        sdsfree(x)