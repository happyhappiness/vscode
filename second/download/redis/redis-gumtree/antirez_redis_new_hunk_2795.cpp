    }
    while (pass != passes) {
        pass++;
        memtest_progress_start("Random fill",pass);
        memtest_fill(m,bytes);
        memtest_progress_end();
        for (j = 0; j < 4; j++) {
            memtest_progress_start("Compare",pass);
            memtest_compare(m,bytes);
            memtest_progress_end();
        }
    }
}

void memtest(size_t megabytes, int passes) {
    if (ioctl(1, TIOCGWINSZ, &ws) == -1) {
        ws.ws_col = 80;
        ws.ws_row = 20;
    }
    memtest_test(megabytes,passes);
    printf("\nYour memory passed this test.\n");
    printf("Please if you are stil in doubt use the following two tools:\n");
