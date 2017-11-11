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