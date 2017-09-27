
/*
 * This routine puts the standard HTML header at the top of the index page.
 * We include the DOCTYPE because we may be using features therefrom (i.e.,
 * HEIGHT and WIDTH attributes on the icons if we're FancyIndexing).
 */
static void emit_preamble(request_rec *r, int xhtml, const char *title)
{
    ap_rvputs(r, xhtml ? DOCTYPE_XHTML_1_0T : DOCTYPE_HTML_3_2,
              "<html>\n <head>\n  <title>Index of ", title,
              "</title>\n </head>\n <body>\n", NULL);
}

static void push_item(apr_array_header_t *arr, char *type, const char *to,
                      const char *path, const char *data)
