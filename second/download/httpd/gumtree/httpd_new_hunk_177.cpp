
/*
 * Emit the anchor for the specified field.  If a field is the key for the
 * current request, the link changes its meaning to reverse the order when
 * selected again.  Non-active fields always start in ascending order.
 */
static void emit_link(request_rec *r, const char *anchor, char column,
                      char curkey, char curdirection,
                      const char *colargs, int nosort)
{
    if (!nosort) {
        char qvalue[9];

        qvalue[0] = '?';
        qvalue[1] = 'C';
        qvalue[2] = '=';
        qvalue[3] = column;
        qvalue[4] = ';';
        qvalue[5] = 'O';
        qvalue[6] = '=';
                    /* reverse? */
        qvalue[7] = ((curkey == column) && (curdirection == D_ASCENDING))
                      ? D_DESCENDING : D_ASCENDING;
        qvalue[8] = '\0';
        ap_rvputs(r, "<a href=\"", qvalue, colargs ? colargs : "",
                     "\">", anchor, "</a>", NULL);
    }
    else {
        ap_rputs(anchor, r);
    }
}

static void output_directories(struct ent **ar, int n,
                               autoindex_config_rec *d, request_rec *r,
                               apr_int32_t autoindex_opts, char keyid,
                               char direction, const char *colargs)
{
    int x;
    apr_size_t rv;
    char *name = r->uri;
    char *tp;
