 \param argc Ignored.
 \param argv Ignored.
 \retval ERR An error occured removing the file.
 \retval OK  The file has been removed.
 */
int
main(int argc, char *argv[])
{
    char buf[UNLINK_BUF_LEN];
    char *t;
    int x;
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    close(2);
    if (open(_PATH_DEVNULL, O_RDWR) < 0) {
        ; // the irony of having to close(2) earlier is that we cannot report this failure.
    }

    while (fgets(buf, sizeof(buf), stdin)) {
        if ((t = strchr(buf, '\n')))
            *t = '\0';
        x = unlink(buf);
        if (x < 0)
            printf("ERR\n");
        else
            printf("OK\n");
    }

    return 0;
}

