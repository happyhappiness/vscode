int
main(int argc, char *argv[])
{
    int t;
    FILE *fp;
    char buf[LOGFILE_BUF_LEN];
    int rotate_count = 10;
    int do_buffer = 1;

    if (argc < 2) {
        printf("Error: usage: %s <logfile>\n", argv[0]);
        exit(1);
    }
    fp = fopen(argv[1], "a");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }
    setbuf(stdout, NULL);
    close(2);
    t = open(_PATH_DEVNULL, O_RDWR);
    assert(t > -1);
    dup2(t, 2);

    while (fgets(buf, LOGFILE_BUF_LEN, stdin)) {
        /* First byte indicates what we're logging! */
        switch (buf[0]) {
        case 'L':
            if (buf[1] != '\0') {
                fprintf(fp, "%s", buf + 1);
                /* try to detect the 32-bit file too big write error and rotate */
                int err = ferror(fp);
                clearerr(fp);
                if (err < 0) {
                    /* file too big - recover by rotating the logs and starting a new one.
                     * out of device space - recover by rotating and hoping that rotation count drops a big one.
                     */
                    if (err == EFBIG || err == ENOSPC) {
                        fprintf(stderr, "WARNING: %s writing %s. Attempting to recover via a log rotation.\n",xstrerr(err),argv[1]);
                        fclose(fp);
                        rotate(argv[1], rotate_count);
                        fp = fopen(argv[1], "a");
                        if (fp == NULL) {
                            perror("fopen");
                            exit(1);
                        }
                        fprintf(fp, "%s", buf + 1);
                    } else {
                        perror("fprintf");
                        exit(1);
                    }
                }
            }
            if (!do_buffer)
                fflush(fp);
            break;
        case 'R':
            fclose(fp);
            rotate(argv[1], rotate_count);
            fp = fopen(argv[1], "a");
            if (fp == NULL) {
                perror("fopen");
                exit(1);
            }
            break;
        case 'T':
            break;
        case 'O':
            break;
        case 'r':
            //fprintf(fp, "SET ROTATE: %s\n", buf + 1);
            rotate_count = atoi(buf + 1);
            break;
        case 'b':
            //fprintf(fp, "SET BUFFERED: %s\n", buf + 1);
            do_buffer = (buf[1] == '1');
            break;
        case 'F':
            fflush(fp);
            break;
        default:
            /* Just in case .. */
            fprintf(fp, "%s", buf);
            break;
        }
    }
    fclose(fp);
    fp = NULL;
    exit(0);
}