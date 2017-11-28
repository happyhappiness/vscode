void
aclParseDenyInfoLine(AclDenyInfoList ** head)
{
    char *t = NULL;
    AclDenyInfoList *A = NULL;
    AclDenyInfoList *B = NULL;
    AclDenyInfoList **T = NULL;
    AclNameList *L = NULL;
    AclNameList **Tail = NULL;

    /* first expect a page name */

    if ((t = ConfigParser::NextToken()) == NULL) {
        debugs(28, DBG_CRITICAL, "aclParseDenyInfoLine: " << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_CRITICAL, "aclParseDenyInfoLine: missing 'error page' parameter.");
        return;
    }

    A = (AclDenyInfoList *)memAllocate(MEM_ACL_DENY_INFO_LIST);
    A->err_page_id = errorReservePageId(t);
    A->err_page_name = xstrdup(t);
    A->next = (AclDenyInfoList *) NULL;
    /* next expect a list of ACL names */
    Tail = &A->acl_list;

    while ((t = ConfigParser::NextToken())) {
        L = (AclNameList *)memAllocate(MEM_ACL_NAME_LIST);
        xstrncpy(L->name, t, ACL_NAME_SZ-1);
        *Tail = L;
        Tail = &L->next;
    }

    if (A->acl_list == NULL) {
        debugs(28, DBG_CRITICAL, "aclParseDenyInfoLine: " << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_CRITICAL, "aclParseDenyInfoLine: deny_info line contains no ACL's, skipping");
        memFree(A, MEM_ACL_DENY_INFO_LIST);
        return;
    }

    for (B = *head, T = head; B; T = &B->next, B = B->next)

        ;   /* find the tail */
    *T = A;
}