static void mod_info_show_cmd(request_rec * r, const ap_directive_t * dir,
                              int nest)
{
    mod_info_indent(r, nest, dir->filename, dir->line_num);
    if (r)
        ap_rprintf(r, "%s <i>%s</i></tt></dd>\n",
                   ap_escape_html(r->pool, dir->directive),
                   ap_escape_html(r->pool, dir->args));
    else
        apr_file_printf(out, "%s %s\n", dir->directive, dir->args);
}