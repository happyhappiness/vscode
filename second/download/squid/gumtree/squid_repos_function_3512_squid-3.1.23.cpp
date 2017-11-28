ACLFilledChecklist *
clientAclChecklistCreate(const acl_access * acl, ClientHttpRequest * http)
{
    ConnStateData * conn = http->getConn();
    ACLFilledChecklist *ch = new ACLFilledChecklist(acl, http->request,
            cbdataReferenceValid(conn) && conn != NULL ? conn->rfc931 : dash_str);

    /*
     * hack for ident ACL. It needs to get full addresses, and a place to store
     * the ident result on persistent connections...
     */
    /* connection oriented auth also needs these two lines for it's operation. */
    /*
     * Internal requests do not have a connection reference, because: A) their
     * byte count may be transformed before being applied to an outbound
     * connection B) they are internal - any limiting on them should be done on
     * the server end.
     */

    if (conn != NULL)
        ch->conn(conn);	/* unreferenced in FilledCheckList.cc */

    return ch;
}