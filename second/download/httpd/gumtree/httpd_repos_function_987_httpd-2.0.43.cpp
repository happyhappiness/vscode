static void do_expand_env(request_rec *r, char *env[],
                          backrefinfo *briRR, backrefinfo *briRC)
{
    int i;
    char buf[MAX_STRING_LEN];

    for (i = 0; env[i] != NULL; i++) {
    do_expand(r, env[i], buf, sizeof(buf), briRR, briRC);
    add_env_variable(r, buf);
    }
}