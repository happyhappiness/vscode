        ap_rvputs(r, comment, "\n", NULL);
    }
    return;                     /* comments are ignored in the
                                   'formatted' form */
}

static void menu_default(request_rec *r, char *menu, char *href, char *text)
{
    if (!strcasecmp(href, "error") || !strcasecmp(href, "nocontent")) {
        return;                 /* don't print such lines, these aren't
                                   really href's */
    }
    if (!strcasecmp(menu, "formatted")) {
        ap_rvputs(r, "<pre>(Default) <a href=\"", href, "\">", text,
               "</a></pre>\n", NULL);
    }
    if (!strcasecmp(menu, "semiformatted")) {
        ap_rvputs(r, "<pre>(Default) <a href=\"", href, "\">", text,
               "</a></pre>\n", NULL);
    }
    if (!strcasecmp(menu, "unformatted")) {
        ap_rvputs(r, "<a href=\"", href, "\">", text, "</a>", NULL);
    }
    return;
}

static void menu_directive(request_rec *r, char *menu, char *href, char *text)
{
    if (!strcasecmp(href, "error") || !strcasecmp(href, "nocontent")) {
        return;                 /* don't print such lines, as this isn't
                                   really an href */
    }
    if (!strcasecmp(menu, "formatted")) {
        ap_rvputs(r, "<pre>          <a href=\"", href, "\">", text,
               "</a></pre>\n", NULL);
    }
    if (!strcasecmp(menu, "semiformatted")) {
        ap_rvputs(r, "<pre>          <a href=\"", href, "\">", text,
               "</a></pre>\n", NULL);
    }
    if (!strcasecmp(menu, "unformatted")) {
        ap_rvputs(r, "<a href=\"", href, "\">", text, "</a>", NULL);
    }
    return;
}

static void menu_footer(request_rec *r)
{
