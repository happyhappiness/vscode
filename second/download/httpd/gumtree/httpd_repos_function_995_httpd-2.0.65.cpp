static void do_expand_cookie( request_rec *r, char *cookie[],
                              backrefinfo *briRR, backrefinfo *briRC)
{
    int i;
    char buf[MAX_STRING_LEN];

    for (i = 0; cookie[i] != NULL; i++) {
        do_expand(r, cookie[i], buf, sizeof(buf), briRR, briRC);
        add_cookie(r, buf);
    }
}