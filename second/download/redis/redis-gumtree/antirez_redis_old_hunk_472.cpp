        errno = EINVAL;
        return -1;
    }
    if (!isatty(STDIN_FILENO)) {
        /* Not a tty: read from file / pipe. */
        if (fgets(buf, buflen, stdin) == NULL) return -1;
        count = strlen(buf);
        if (count && buf[count-1] == '\n') {
            count--;
            buf[count] = '\0';
        }
    } else {
        /* Interactive editing. */
        if (enableRawMode(STDIN_FILENO) == -1) return -1;
        count = linenoiseEdit(STDIN_FILENO, STDOUT_FILENO, buf, buflen, prompt);
        disableRawMode(STDIN_FILENO);
        printf("\n");
    }
    return count;
}

/* The high level function that is the main API of the linenoise library.
