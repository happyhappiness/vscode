static void emit_preamble(request_rec *r, int xhtml, const char *title)
{
    ap_rvputs(r, xhtml ? DOCTYPE_XHTML_1_0T : DOCTYPE_HTML_3_2,
              "<html>\n <head>\n  <title>Index of ", title,
              "</title>\n </head>\n <body>\n", NULL);
}