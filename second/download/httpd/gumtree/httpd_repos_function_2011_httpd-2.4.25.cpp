static void create_radio(const char *name, unsigned int flag, request_rec *r)
{
    ap_rvputs(r, "<td><label for='", name, "1'>On</label> <input name='", name, "' id='", name, "1' value='1' type=radio", NULL);
    if (flag)
        ap_rputs(" checked", r);
    ap_rvputs(r, "> <br/> <label for='", name, "0'>Off</label> <input name='", name, "' id='", name, "0' value='0' type=radio", NULL);
    if (!flag)
        ap_rputs(" checked", r);
    ap_rputs("></td>\n", r);
}