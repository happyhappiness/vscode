static void beep() {
    fprintf(stderr, "\x7");
    fflush(stderr);
}