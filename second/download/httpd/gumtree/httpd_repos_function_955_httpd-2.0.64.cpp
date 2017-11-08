static void menu_footer(request_rec *r)
{
    ap_rputs("\n\n</body>\n</html>\n", r);         /* finish the menu */
}