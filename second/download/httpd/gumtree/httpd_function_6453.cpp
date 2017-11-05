static void menu_default(request_rec *r, const char *menu, const char *href, const char *text)
{
    char *ehref, *etext;
    if (!strcasecmp(href, "error") || !strcasecmp(href, "nocontent")) {
        return;                 /* don't print such lines, these aren't
                                   really href's */
    }

    ehref = ap_escape_uri(r->pool, href);
    etext = ap_escape_html(r->pool, text);

    if (!strcasecmp(menu, "formatted")) {
        ap_rvputs(r, "<pre>(Default) <a href=\"", ehref, "\">", etext,
                     "</a></pre>\n", NULL);
    }
    else if (!strcasecmp(menu, "semiformatted")) {
        ap_rvputs(r, "<pre>(Default) <a href=\"", ehref, "\">", etext,
               "</a></pre>\n", NULL);
    }
    else if (!strcasecmp(menu, "unformatted")) {
        ap_rvputs(r, "<a href=\"", ehref, "\">", etext, "</a>", NULL);
    }
    return;
}