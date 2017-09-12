void memtest_progress_end(void) {
    printf("\x1b[H\x1b[2J");    /* Cursor home, clear screen. */
}