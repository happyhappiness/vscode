            }
        }
    }
    printf("\r\n");
}

/* Linenoise completion callback. */
static void completionCallback(const char *buf, linenoiseCompletions *lc) {
    size_t startpos = 0;
    int mask;
    int i;
    size_t matchlen;
    sds tmp;
