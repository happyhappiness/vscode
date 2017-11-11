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