bool
icpAccessAllowed(Ip::Address &from, HttpRequest * icp_request)
{
    /* absent any explicit rules, we deny all */
    if (!Config.accessList.icp)
        return false;

    ACLFilledChecklist checklist(Config.accessList.icp, icp_request, NULL);
    checklist.src_addr = from;
    checklist.my_addr.SetNoAddr();
    return (checklist.fastCheck() == ACCESS_ALLOWED);
}