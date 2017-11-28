int
aclMatchEui(SplayNode<Eui::Eui64 *> **dataptr, Ip::Address &c)
{
    Eui::Eui64 result;
    SplayNode<Eui::Eui64 *> **Top = dataptr;

    if (result.lookup(c)) {
        /* Do ACL match lookup */
        *Top = (*Top)->splay(&result, aclEui64Compare);
        debugs(28, 3, "aclMatchEui: '" << c << "' " << (splayLastResult ? "NOT found" : "found"));
        return (0 == splayLastResult);
    }

    /*
     * Address was not found on any interface
     */
    debugs(28, 3, "aclMatchEui: " << c << " NOT found");
    return 0;
}