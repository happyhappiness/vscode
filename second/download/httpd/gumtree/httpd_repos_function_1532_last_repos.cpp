static void menu_comment(request_rec *r, char *menu, char *comment)
{
    /* comments are ignored in the 'formatted' form */
    if (!strcasecmp(menu, "formatted")) {
        ap_rputs("\n", r);         /* print just a newline if 'formatted' */
    }
    else if (!strcasecmp(menu, "semiformatted") && *comment) {
        ap_rvputs(r, comment, "\n", NULL);
    }
    else if (!strcasecmp(menu, "unformatted") && *comment) {
        ap_rvputs(r, comment, "\n", NULL);
    }
}