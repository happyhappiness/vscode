static void menu_header(request_rec *r, char *menu)
{
    ap_set_content_type(r, "text/html");

    ap_rvputs(r, DOCTYPE_HTML_3_2, "<html><head>\n<title>Menu for ", r->uri,
           "</title>\n</head><body>\n", NULL);

    if (!strcasecmp(menu, "formatted")) {
        ap_rvputs(r, "<h1>Menu for ", r->uri, "</h1>\n<hr />\n\n", NULL);
    }

    return;
}