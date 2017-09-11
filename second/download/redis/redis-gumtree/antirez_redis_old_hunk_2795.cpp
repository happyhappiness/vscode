    }
    while (pass != passes) {
        pass++;
        printf("PASS %d... ", pass);
        fflush(stdout);
        memtest_fill(m,bytes);
        memtest_compare(m,bytes);
        printf("ok\n");
    }
}

void memtest(size_t megabytes, int passes) {
    memtest_test(megabytes,passes);
    printf("\nYour memory passed this test.\n");
    printf("Please if you are stil in doubt use the following two tools:\n");
