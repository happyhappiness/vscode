static const char *proxy_interpolate(request_rec *r, const char *str)
{
    /* Interpolate an env str in a configuration string
     * Syntax ${var} --> value_of(var)
     * Method: replace one var, and recurse on remainder of string
     * Nothing clever here, and crap like nested vars may do silly things
     * but we'll at least avoid sending the unwary into a loop
     */
    const char *start;
    const char *end;
    const char *var;
    const char *val;
    const char *firstpart;

    start = ap_strstr_c(str, "${");
    if (start == NULL) {
        return str;
    }
    end = ap_strchr_c(start+2, '}');
    if (end == NULL) {
        return str;
    }
    /* OK, this is syntax we want to interpolate.  Is there such a var ? */
    var = apr_pstrndup(r->pool, start+2, end-(start+2));
    val = apr_table_get(r->subprocess_env, var);
    firstpart = apr_pstrndup(r->pool, str, (start-str));

    if (val == NULL) {
        return apr_pstrcat(r->pool, firstpart,
                           proxy_interpolate(r, end+1), NULL);
    }
    else {
        return apr_pstrcat(r->pool, firstpart, val,
                           proxy_interpolate(r, end+1), NULL);
    }
}