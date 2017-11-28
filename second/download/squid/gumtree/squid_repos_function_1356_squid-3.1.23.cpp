int
icpAccessAllowed(IpAddress &from, HttpRequest * icp_request)
{
    /* absent an explicit allow, we deny all */
    if (!Config.accessList.icp)
        return 0;

    ACLFilledChecklist checklist(Config.accessList.icp, icp_request, NULL);
    checklist.src_addr = from;
    checklist.my_addr.SetNoAddr();
    int result = checklist.fastCheck();
    return result;
}