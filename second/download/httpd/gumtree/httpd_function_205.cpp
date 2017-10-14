static void emit_preamble(request_rec *r, char *title)
{
    ap_rvputs(r, DOCTYPE_HTML_3_2,
              "<html>\n <head>\n  <title>Index of ", title,
              "</title>\n </head>\n <body>\n", NULL);
}