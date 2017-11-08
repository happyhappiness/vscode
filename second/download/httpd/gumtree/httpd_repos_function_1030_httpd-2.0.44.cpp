static void add_env_variable(request_rec *r, char *s)
{
    char var[MAX_STRING_LEN];
    char val[MAX_STRING_LEN];
    char *cp;
    int n;

    if ((cp = strchr(s, ':')) != NULL) {
        n = ((cp-s) > MAX_STRING_LEN-1 ? MAX_STRING_LEN-1 : (cp-s));
        memcpy(var, s, n);
        var[n] = '\0';
        apr_cpystrn(val, cp+1, sizeof(val));
        apr_table_set(r->subprocess_env, var, val);
        rewritelog(r, 5, "setting env variable '%s' to '%s'", var, val);
    }
}