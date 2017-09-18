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
