    /* does it look like a table? */

    if (!strchr(buf, '\t') || *buf == '\t') {
        /* nope, just text */
        if (table_line_num)
            out.append("</table>\n<pre>", 14);
        out.appendf("%s", html_quote(buf));
        table_line_num = 0;
        return;
    }

    /* start html table */
    if (!table_line_num) {
