
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
