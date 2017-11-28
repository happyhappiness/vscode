static const char *
munge_other_line(const char *buf, cachemgr_request * req)
{
    static const char *ttags[] = {"td", "th"};

    static char html[4096];
    static int table_line_num = 0;
    static int next_is_header = 0;
    int is_header = 0;
    const char *ttag;
    char *buf_copy;
    char *x, *p;
    int l = 0;
    /* does it look like a table? */

    if (!strchr(buf, '\t') || *buf == '\t') {
        /* nope, just text */
        snprintf(html, sizeof(html), "%s%s",
                 table_line_num ? "</table>\n<pre>" : "", html_quote(buf));
        table_line_num = 0;
        return html;
    }

    /* start html table */
    if (!table_line_num) {
        l += snprintf(html + l, sizeof(html) - l, "</pre><table cellpadding=\"2\" cellspacing=\"1\">\n");
        next_is_header = 0;
    }

    /* remove '\n' */
    is_header = (!table_line_num || next_is_header) && !strchr(buf, ':') && !is_number(buf);

    ttag = ttags[is_header];

    /* record starts */
    l += snprintf(html + l, sizeof(html) - l, "<tr>");

    /* substitute '\t' */
    buf_copy = x = xstrdup(buf);

    if ((p = strchr(x, '\n')))
        *p = '\0';

    while (x && strlen(x)) {
        int column_span = 1;
        const char *cell = xstrtok(&x, '\t');

        while (x && *x == '\t') {
            ++column_span;
            ++x;
        }

        l += snprintf(html + l, sizeof(html) - l, "<%s colspan=\"%d\" align=\"%s\">%s</%s>",
                      ttag, column_span,
                      is_header ? "center" : is_number(cell) ? "right" : "left",
                      html_quote(cell), ttag);
    }

    xfree(buf_copy);
    /* record ends */
    snprintf(html + l, sizeof(html) - l, "</tr>\n");
    next_is_header = is_header && strstr(buf, "\t\t");
    ++table_line_num;
    return html;
}