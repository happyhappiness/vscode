static int find_test_name(const char *testname) {
    int i;
    for (i = 0; testlist[i] != NULL; i++) {
        if (!strcmp(testlist[i], testname)) {
            return 1;
        }
    }
    return 0;
}