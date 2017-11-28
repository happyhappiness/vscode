void
aclParseDenyInfoLine(AclDenyInfoList ** head)
{
    char *t = NULL;
    AclDenyInfoList *B;
    AclDenyInfoList **T;
    AclNameList *L = NULL;
    AclNameList **Tail = NULL;

    /* first expect a page name */

    if ((t = ConfigParser::NextToken()) == NULL) {
        debugs(28, DBG_CRITICAL, "aclParseDenyInfoLine: " << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_CRITICAL, "aclParseDenyInfoLine: missing 'error page' parameter.");
        return;
    }

    AclDenyInfoList *A = new AclDenyInfoList(t);

    /* next expect a list of ACL names */
    Tail = &A->acl_list;

    while ((t = ConfigParser::NextToken())) {
        L = new AclNameList(t);
        *Tail = L;
        Tail = &L->next;
    }

    if (A->acl_list == NULL) {
        debugs(28, DBG_CRITICAL, "aclParseDenyInfoLine: " << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_CRITICAL, "aclParseDenyInfoLine: deny_info line contains no ACL's, skipping");
        delete A;
        return;
    }

    for (B = *head, T = head; B; T = &B->next, B = B->next)

        ;   /* find the tail */
    *T = A;
}