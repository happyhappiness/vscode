static void
munge_other_line(MemBuf &out, const char *buf, cachemgr_request *)
{
    static const char *ttags[] = {"td", "th"};

    static int table_line_num = 0;
    static int next_is_header = 0;
    int is_header = 0;
    const char *ttag;
    char *buf_copy;
    char *x, *p;
    /* does it look like a table? */

    if (!strchr(buf, '\t') || *buf == '\t') {
        /* nope, just text */
        if (table_line_num)
            out.append("</table>\n<pre>", 14);
        out.Printf("%s", html_quote(buf));
        table_line_num = 0;
        return;
    }

    /* start html table */
    if (!table_line_num) {
        out.append("</pre><table cellpadding=\"2\" cellspacing=\"1\">\n", 46);
        next_is_header = 0;
    }

    /* remove '\n' */
    is_header = (!table_line_num || next_is_header) && !strchr(buf, ':') && !is_number(buf);

    ttag = ttags[is_header];

    /* record starts */
    out.append("<tr>", 4);

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

        out.Printf("<%s colspan=\"%d\" align=\"%s\">%s</%s>",
                   ttag, column_span,
                   is_header ? "center" : is_number(cell) ? "right" : "left",
                   html_quote(cell), ttag);
    }

    xfree(buf_copy);
    /* record ends */
    out.append("</tr>\n", 6);
    next_is_header = is_header && strstr(buf, "\t\t");
    ++table_line_num;
}