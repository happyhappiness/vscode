            fprintf(stderr,"Error reading bulk length while SYNCing\n");
            exit(1);
        }
        if (*p == '\n') break;
        p++;
    }
    *p = '\0';
    if (buf[0] == '-') {
