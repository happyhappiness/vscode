int
aclMatchArp(SplayNode<Eui::Eui48 *> **dataptr, Ip::Address &c)
{
    Eui::Eui48 result;
    SplayNode<Eui::Eui48 *> **Top = dataptr;

    if (result.lookup(c)) {
        /* Do ACL match lookup */
        *Top = (*Top)->splay(&result, aclArpCompare);
        debugs(28, 3, "aclMatchArp: '" << c << "' " << (splayLastResult ? "NOT found" : "found"));
        return (0 == splayLastResult);
    }

    /*
     * Address was not found on any interface
     */
    debugs(28, 3, "aclMatchArp: " << c << " NOT found");
    return 0;
}