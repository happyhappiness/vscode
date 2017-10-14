static void mod_info_show_close(request_rec * r, const ap_directive_t * dir,
                                int nest)
{
    const char *dirname = dir->directive;
    mod_info_indent(r, nest, dir->filename, 0);
    if (*dirname == '<') {
        if (r)
            ap_rprintf(r, "&lt;/%s&gt;</tt></dd>",
                       ap_escape_html(r->pool, dirname + 1));
        else
            apr_file_printf(out, "</%s>\n", dirname + 1);
    }
    else {
        if (r)
            ap_rprintf(r, "/%s</tt></dd>", ap_escape_html(r->pool, dirname));
        else
            apr_file_printf(out, "/%s\n", dirname);
    }
}