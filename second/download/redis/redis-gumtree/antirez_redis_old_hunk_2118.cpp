        rawmode = 0;
}

/* At exit we'll try to fix the terminal to the initial conditions. */
static void linenoiseAtExit(void) {
    disableRawMode(STDIN_FILENO);
    freeHistory();
}

static int getColumns(void) {
    struct winsize ws;

    if (ioctl(1, TIOCGWINSZ, &ws) == -1) return 80;
    return ws.ws_col;
}

static void refreshLine(int fd, const char *prompt, char *buf, size_t len, size_t pos, size_t cols) {
    char seq[64];
    size_t plen = strlen(prompt);
    
    while((plen+pos) >= cols) {
        buf++;
        len--;
        pos--;
    }
    while (plen+len > cols) {
        len--;
    }

    /* Cursor to left edge */
    snprintf(seq,64,"\x1b[0G");
    if (write(fd,seq,strlen(seq)) == -1) return;
    /* Write the prompt and the current buffer content */
    if (write(fd,prompt,strlen(prompt)) == -1) return;
    if (write(fd,buf,len) == -1) return;
    /* Erase to right */
    snprintf(seq,64,"\x1b[0K");
    if (write(fd,seq,strlen(seq)) == -1) return;
    /* Move cursor to original position. */
    snprintf(seq,64,"\x1b[0G\x1b[%dC", (int)(pos+plen));
    if (write(fd,seq,strlen(seq)) == -1) return;
}

static void beep() {
    fprintf(stderr, "\x7");
    fflush(stderr);
}

static void freeCompletions(linenoiseCompletions *lc) {
    size_t i;
    for (i = 0; i < lc->len; i++)
