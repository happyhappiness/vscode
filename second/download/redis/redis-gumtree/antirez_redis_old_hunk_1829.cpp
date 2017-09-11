
        printf("'%c' %02x (%d) (type quit to exit)\n",
            isprint(c) ? c : '?', (int)c, (int)c);
        printf("\x1b[0G"); /* Go left edge manually, we are in raw mode. */
        fflush(stdout);
    }
    disableRawMode(STDIN_FILENO);
