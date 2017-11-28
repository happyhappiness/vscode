static bool
htcpAccessAllowed(acl_access * acl, htcpSpecifier * s, Ip::Address &from)
{
    /* default deny if no access list present */
    if (!acl)
        return false;

    ACLFilledChecklist checklist(acl, s->request, NULL);
    checklist.src_addr = from;
    checklist.my_addr.SetNoAddr();
    return (checklist.fastCheck() == ACCESS_ALLOWED);
}