    return c; /* Return last read character */
}

void linenoiseClearScreen(void) {
    if (write(STDIN_FILENO,"\x1b[H\x1b[2J",7) <= 0) {
        /* nothing to do, just to avoid warning. */
    }
}

static int linenoisePrompt(int fd, char *buf, size_t buflen, const char *prompt) {
    size_t plen = strlen(prompt);
    size_t pos = 0;
    size_t len = 0;
    size_t cols = getColumns();
    int history_index = 0;
    size_t old_pos;
    size_t diff;

    buf[0] = '\0';
    buflen--; /* Make sure there is always space for the nulterm */

    /* The latest history entry is always our current buffer, that
     * initially is just an empty string. */
    linenoiseHistoryAdd("");
    
    if (write(fd,prompt,plen) == -1) return -1;
    while(1) {
        char c;
        int nread;
        char seq[2], seq2[2];

        nread = read(fd,&c,1);
        if (nread <= 0) return len;

        /* Only autocomplete when the callback is set. It returns < 0 when
         * there was an error reading from fd. Otherwise it will return the
         * character that should be handled next. */
        if (c == 9 && completionCallback != NULL) {
            c = completeLine(fd,prompt,buf,buflen,&len,&pos,cols);
            /* Return on errors */
            if (c < 0) return len;
            /* Read next character when 0 */
            if (c == 0) continue;
        }

        switch(c) {
        case 13:    /* enter */
            history_len--;
            free(history[history_len]);
            return (int)len;
        case 3:     /* ctrl-c */
            errno = EAGAIN;
            return -1;
        case 127:   /* backspace */
        case 8:     /* ctrl-h */
            if (pos > 0 && len > 0) {
                memmove(buf+pos-1,buf+pos,len-pos);
                pos--;
                len--;
                buf[len] = '\0';
                refreshLine(fd,prompt,buf,len,pos,cols);
            }
            break;
        case 4:     /* ctrl-d, remove char at right of cursor */
            if (len > 1 && pos < (len-1)) {
                memmove(buf+pos,buf+pos+1,len-pos);
                len--;
                buf[len] = '\0';
                refreshLine(fd,prompt,buf,len,pos,cols);
            } else if (len == 0) {
                history_len--;
                free(history[history_len]);
                return -1;
            }
            break;
        case 20:    /* ctrl-t */
            if (pos > 0 && pos < len) {
                int aux = buf[pos-1];
                buf[pos-1] = buf[pos];
                buf[pos] = aux;
                if (pos != len-1) pos++;
                refreshLine(fd,prompt,buf,len,pos,cols);
            }
            break;
        case 2:     /* ctrl-b */
            goto left_arrow;
        case 6:     /* ctrl-f */
            goto right_arrow;
        case 16:    /* ctrl-p */
            seq[1] = 65;
            goto up_down_arrow;
        case 14:    /* ctrl-n */
            seq[1] = 66;
            goto up_down_arrow;
            break;
        case 27:    /* escape sequence */
            if (read(fd,seq,2) == -1) break;
            if (seq[0] == 91 && seq[1] == 68) {
left_arrow:
                /* left arrow */
                if (pos > 0) {
                    pos--;
                    refreshLine(fd,prompt,buf,len,pos,cols);
                }
            } else if (seq[0] == 91 && seq[1] == 67) {
right_arrow:
                /* right arrow */
                if (pos != len) {
                    pos++;
                    refreshLine(fd,prompt,buf,len,pos,cols);
                }
            } else if (seq[0] == 91 && (seq[1] == 65 || seq[1] == 66)) {
up_down_arrow:
                /* up and down arrow: history */
                if (history_len > 1) {
                    /* Update the current history entry before to
                     * overwrite it with tne next one. */
                    free(history[history_len-1-history_index]);
                    history[history_len-1-history_index] = strdup(buf);
                    /* Show the new entry */
                    history_index += (seq[1] == 65) ? 1 : -1;
                    if (history_index < 0) {
                        history_index = 0;
                        break;
                    } else if (history_index >= history_len) {
                        history_index = history_len-1;
                        break;
                    }
                    strncpy(buf,history[history_len-1-history_index],buflen);
                    buf[buflen] = '\0';
                    len = pos = strlen(buf);
                    refreshLine(fd,prompt,buf,len,pos,cols);
                }
            } else if (seq[0] == 91 && seq[1] > 48 && seq[1] < 55) {
                /* extended escape */
                if (read(fd,seq2,2) == -1) break;
                if (seq[1] == 51 && seq2[0] == 126) {
                    /* delete */
                    if (len > 0 && pos < len) {
                        memmove(buf+pos,buf+pos+1,len-pos-1);
                        len--;
                        buf[len] = '\0';
                        refreshLine(fd,prompt,buf,len,pos,cols);
                    }
                }
            }
            break;
        default:
            if (len < buflen) {
                if (len == pos) {
                    buf[pos] = c;
                    pos++;
                    len++;
                    buf[len] = '\0';
                    if (plen+len < cols) {
                        /* Avoid a full update of the line in the
                         * trivial case. */
                        if (write(fd,&c,1) == -1) return -1;
                    } else {
                        refreshLine(fd,prompt,buf,len,pos,cols);
                    }
                } else {
                    memmove(buf+pos+1,buf+pos,len-pos);
                    buf[pos] = c;
                    len++;
                    pos++;
                    buf[len] = '\0';
                    refreshLine(fd,prompt,buf,len,pos,cols);
                }
            }
            break;
        case 21: /* Ctrl+u, delete the whole line. */
            buf[0] = '\0';
            pos = len = 0;
            refreshLine(fd,prompt,buf,len,pos,cols);
            break;
        case 11: /* Ctrl+k, delete from current to end of line. */
            buf[pos] = '\0';
            len = pos;
            refreshLine(fd,prompt,buf,len,pos,cols);
            break;
        case 1: /* Ctrl+a, go to the start of the line */
            pos = 0;
            refreshLine(fd,prompt,buf,len,pos,cols);
            break;
        case 5: /* ctrl+e, go to the end of the line */
            pos = len;
            refreshLine(fd,prompt,buf,len,pos,cols);
            break;
        case 12: /* ctrl+l, clear screen */
            linenoiseClearScreen();
            refreshLine(fd,prompt,buf,len,pos,cols);
            break;
        case 23: /* ctrl+w, delete previous word */
            old_pos = pos;
            while (pos > 0 && buf[pos-1] == ' ')
                pos--;
            while (pos > 0 && buf[pos-1] != ' ')
                pos--;
            diff = old_pos - pos;
            memmove(&buf[pos], &buf[old_pos], len-old_pos+1);
            len -= diff;
            refreshLine(fd,prompt,buf,len,pos,cols);
            break;
        }
    }
    return len;
}

static int linenoiseRaw(char *buf, size_t buflen, const char *prompt) {
    int fd = STDIN_FILENO;
    int count;

    if (buflen == 0) {
        errno = EINVAL;
        return -1;
    }
    if (!isatty(STDIN_FILENO)) {
        if (fgets(buf, buflen, stdin) == NULL) return -1;
        count = strlen(buf);
        if (count && buf[count-1] == '\n') {
            count--;
            buf[count] = '\0';
        }
    } else {
        if (enableRawMode(fd) == -1) return -1;
        count = linenoisePrompt(fd, buf, buflen, prompt);
        disableRawMode(fd);
        printf("\n");
    }
    return count;
}

char *linenoise(const char *prompt) {
    char buf[LINENOISE_MAX_LINE];
    int count;
