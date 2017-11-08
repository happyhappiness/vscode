static void mod_info_indent(request_rec * r, int nest,
                            const char *thisfn, int linenum)
{
    int i;
    const char *prevfn =
        ap_get_module_config(r->request_config, &info_module);
    if (thisfn == NULL)
        thisfn = "*UNKNOWN*";
    if (prevfn == NULL || 0 != strcmp(prevfn, thisfn)) {
        thisfn = ap_escape_html(r->pool, thisfn);
        ap_rprintf(r, "<dd><tt><strong>In file: %s</strong></tt></dd>\n",
                   thisfn);
        ap_set_module_config(r->request_config, &info_module,
                             (void *) thisfn);
    }

    ap_rputs("<dd><tt>", r);
    put_int_flush_right(r, linenum > 0 ? linenum : 0, 4);
    ap_rputs(":&nbsp;", r);

    for (i = 1; i <= nest; ++i) {
        ap_rputs("&nbsp;&nbsp;", r);
    }
}