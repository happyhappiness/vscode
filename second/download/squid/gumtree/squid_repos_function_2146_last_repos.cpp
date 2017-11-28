static bool
htcpAccessAllowed(acl_access * acl, const htcpSpecifier::Pointer &s, Ip::Address &from)
{
    /* default deny if no access list present */
    if (!acl)
        return false;

    ACLFilledChecklist checklist(acl, s->request.getRaw(), nullptr);
    checklist.src_addr = from;
    checklist.my_addr.setNoAddr();
    return checklist.fastCheck().allowed();
}