}

static void menu_header(request_rec *r, char *menu)
{
    ap_set_content_type(r, "text/html; charset=ISO-8859-1");

    ap_rvputs(r, DOCTYPE_HTML_3_2, "<html><head>\n<title>Menu for ", 
              ap_escape_html(r->pool, r->uri),
              "</title>\n</head><body>\n", NULL);

    if (!strcasecmp(menu, "formatted")) {
        ap_rvputs(r, "<h1>Menu for ", 
                  ap_escape_html(r->pool, r->uri),
                  "</h1>\n<hr />\n\n", NULL);
    }

    return;
}

static void menu_blank(request_rec *r, char *menu)
{
    if (!strcasecmp(menu, "formatted")) {
        ap_rputs("\n", r);
    }
    if (!strcasecmp(menu, "semiformatted")) {
        ap_rputs("<br />\n", r);
    }
    if (!strcasecmp(menu, "unformatted")) {
        ap_rputs("\n", r);
    }
    return;
}

static void menu_comment(request_rec *r, char *menu, char *comment)
{
    if (!strcasecmp(menu, "formatted")) {
        ap_rputs("\n", r);         /* print just a newline if 'formatted' */
    }
    if (!strcasecmp(menu, "semiformatted") && *comment) {
        ap_rvputs(r, comment, "\n", NULL);
    }
    if (!strcasecmp(menu, "unformatted") && *comment) {
        ap_rvputs(r, comment, "\n", NULL);
    }
    return;                     /* comments are ignored in the
                                   'formatted' form */
}

