}

static void put_int_flush_right(request_rec * r, int i, int field)
{
    if (field > 1 || i > 9)
        put_int_flush_right(r, i / 10, field - 1);
    if (i)
        ap_rputc('0' + i % 10, r);
    else
        ap_rputs("&nbsp;", r);
}

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

static void mod_info_show_cmd(request_rec * r, const ap_directive_t * dir,
                              int nest)
{
    mod_info_indent(r, nest, dir->filename, dir->line_num);
    ap_rprintf(r, "%s <i>%s</i></tt></dd>\n",
               ap_escape_html(r->pool, dir->directive),
               ap_escape_html(r->pool, dir->args));
}

static void mod_info_show_open(request_rec * r, const ap_directive_t * dir,
                               int nest)
{
    mod_info_indent(r, nest, dir->filename, dir->line_num);
    ap_rprintf(r, "%s %s</tt></dd>\n",
               ap_escape_html(r->pool, dir->directive),
               ap_escape_html(r->pool, dir->args));
}

static void mod_info_show_close(request_rec * r, const ap_directive_t * dir,
                                int nest)
{
    const char *dirname = dir->directive;
    mod_info_indent(r, nest, dir->filename, 0);
    if (*dirname == '<') {
        ap_rprintf(r, "&lt;/%s&gt;</tt></dd>",
                   ap_escape_html(r->pool, dirname + 1));
    }
    else {
        ap_rprintf(r, "/%s</tt></dd>", ap_escape_html(r->pool, dirname));
    }
}

static int mod_info_has_cmd(const command_rec * cmds, ap_directive_t * dir)
{
    const command_rec *cmd;
