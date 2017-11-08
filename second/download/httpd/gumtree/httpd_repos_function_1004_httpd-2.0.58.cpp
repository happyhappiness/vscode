static char *select_random_value_part(request_rec *r, char *value)
{
    char *buf;
    int n, i, k;

    /*  count number of distinct values  */
    for (n = 1, i = 0; value[i] != '\0'; i++) {
        if (value[i] == '|') {
            n++;
        }
    }

    /*  when only one value we have no option to choose  */
    if (n == 1) {
        return value;
    }

    /*  else randomly select one  */
    k = rewrite_rand(1, n);

    /*  and grep it out  */
    for (n = 1, i = 0; value[i] != '\0'; i++) {
        if (n == k) {
            break;
        }
        if (value[i] == '|') {
            n++;
        }
    }
    buf = apr_pstrdup(r->pool, &value[i]);
    for (i = 0; buf[i] != '\0' && buf[i] != '|'; i++)
        ;
    buf[i] = '\0';
    return buf;
}