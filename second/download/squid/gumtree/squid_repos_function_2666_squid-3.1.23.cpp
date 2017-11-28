static int
htcpAccessCheck(acl_access * acl, htcpSpecifier * s, IpAddress &from)
{
    /* default deny if no access list present */
    if (!acl)
        return 0;

    ACLFilledChecklist checklist(acl, s->request, NULL);
    checklist.src_addr = from;
    checklist.my_addr.SetNoAddr();
    int result = checklist.fastCheck();
    return result;
}