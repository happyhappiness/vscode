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