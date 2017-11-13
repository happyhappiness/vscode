static void mod_info_indent(request_rec * r, int nest,
                            const char *thisfn, int linenum)
{
    int i;
    const char *prevfn = get_fn_info(r);
    if (thisfn == NULL)
        thisfn = "*UNKNOWN*";
    if (prevfn == NULL || 0 != strcmp(prevfn, thisfn)) {
        if (r) {
            thisfn = ap_escape_html(r->pool, thisfn);
            ap_rprintf(r, "<dd><tt><strong>In file: %s</strong></tt></dd>\n",
                   thisfn);
        }
        else {
            apr_file_printf(out, "# In file: %s\n", thisfn);
        }
        set_fn_info(r, thisfn);
    }

    if (r) {
        ap_rputs("<dd><tt>", r);
        put_int_flush_right(r, linenum > 0 ? linenum : 0, 4);
        ap_rputs(":&nbsp;", r);
    }
    else if (linenum > 0) {
        for (i = 1; i <= nest; ++i)
            apr_file_printf(out, "  ");
        apr_file_putc('#', out);
        put_int_flush_right(r, linenum, 4);
        apr_file_printf(out, ":\n");
    }

    for (i = 1; i <= nest; ++i) {
        if (r)
            ap_rputs("&nbsp;&nbsp;", r);
        else
            apr_file_printf(out, "  ");
    }
}