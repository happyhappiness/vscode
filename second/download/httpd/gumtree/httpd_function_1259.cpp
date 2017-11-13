static void emit_preamble(request_rec *r, int xhtml, const char *title)
{
    autoindex_config_rec *d;

    d = (autoindex_config_rec *) ap_get_module_config(r->per_dir_config,
                                                      &autoindex_module);

    if (xhtml) {
        ap_rvputs(r, DOCTYPE_XHTML_1_0T,
                  "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                  " <head>\n  <title>Index of ", title,
                  "</title>\n", NULL);
    } else {
        ap_rvputs(r, DOCTYPE_HTML_3_2,
                  "<html>\n <head>\n"
                  "  <title>Index of ", title,
                  "</title>\n", NULL);
    }

    if (d->style_sheet != NULL) {
        ap_rvputs(r, "  <link rel=\"stylesheet\" href=\"", d->style_sheet,
                "\" type=\"text/css\"", xhtml ? " />\n" : ">\n", NULL);
    }
    ap_rvputs(r, " </head>\n <body>\n", NULL);
}