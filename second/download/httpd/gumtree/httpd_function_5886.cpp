static void create_radio(const char *name, unsigned int flag, request_rec *r)
{
    ap_rvputs(r, "<td>On <input name='", name, "' id='", name, "' value='1' type=radio", NULL);
    if (flag)
        ap_rputs(" checked", r);
    ap_rvputs(r, "> <br/> Off <input name='", name, "' id='", name, "' value='0' type=radio", NULL);
    if (!flag)
        ap_rputs(" checked", r);
    ap_rputs("></td>\n", r);
}