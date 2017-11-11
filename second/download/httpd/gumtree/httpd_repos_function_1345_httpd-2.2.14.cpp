static void mod_info_show_cmd(request_rec * r, const ap_directive_t * dir,
                              int nest)
{
    mod_info_indent(r, nest, dir->filename, dir->line_num);
    ap_rprintf(r, "%s <i>%s</i></tt></dd>\n",
               ap_escape_html(r->pool, dir->directive),
               ap_escape_html(r->pool, dir->args));
}