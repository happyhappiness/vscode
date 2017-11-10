static void menu_directive(request_rec *r, const char *menu, const char *href, const char *text)
{
    char *ehref, *etext;
    if (!strcasecmp(href, "error") || !strcasecmp(href, "nocontent")) {
        return;                 /* don't print such lines, as this isn't
                                   really an href */
    }

    ehref = ap_escape_uri(r->pool, href);
    etext = ap_escape_html(r->pool, text);

    if (!strcasecmp(menu, "formatted")) {
        ap_rvputs(r, "<pre>          <a href=\"", ehref, "\">", etext,
               "</a></pre>\n", NULL);
    }
    else if (!strcasecmp(menu, "semiformatted")) {
        ap_rvputs(r, "<pre>          <a href=\"", ehref, "\">", etext,
               "</a></pre>\n", NULL);
    }
    else if (!strcasecmp(menu, "unformatted")) {
        ap_rvputs(r, "<a href=\"", ehref, "\">", etext, "</a>", NULL);
    }
    return;
}