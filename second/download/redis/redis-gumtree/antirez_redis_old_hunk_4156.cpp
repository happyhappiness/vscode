        errno = EINVAL;
        return -1;
    }
    if (enableRawMode(fd) == -1) return -1;
    count = linenoisePrompt(fd, buf, buflen, prompt);
    disableRawMode(fd);
    printf("\n");
    return count;
}

char *linenoise(const char *prompt) {
    char buf[LINENOISE_MAX_LINE];
    int count;

    count = linenoiseRaw(buf,LINENOISE_MAX_LINE,prompt);
    if (count == -1) return NULL;
    return strdup(buf);
}

/* Using a circular buffer is smarter, but a bit more complex to handle. */
int linenoiseHistoryAdd(char *line) {
    if (history_max_len == 0) return 0;
    if (history == 0) {
        history = malloc(sizeof(char*)*history_max_len);
        if (history == NULL) return 0;
        memset(history,0,(sizeof(char*)*history_max_len));
    }
    line = strdup(line);
    if (!line) return 0;
    if (history_len == history_max_len) {
        memmove(history,history+1,sizeof(char*)*(history_max_len-1));
        history_len--;
    }
    history[history_len] = line;
    history_len++;
    return 1;
}
