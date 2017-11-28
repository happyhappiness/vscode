void
aclParseDenyInfoLine(acl_deny_info_list ** head)
{
    char *t = NULL;
    acl_deny_info_list *A = NULL;
    acl_deny_info_list *B = NULL;
    acl_deny_info_list **T = NULL;
    acl_name_list *L = NULL;
    acl_name_list **Tail = NULL;

    /* first expect a page name */

    if ((t = strtok(NULL, w_space)) == NULL) {
        debugs(28, 0, "aclParseDenyInfoLine: " << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, 0, "aclParseDenyInfoLine: missing 'error page' parameter.");
        return;
    }

    A = (acl_deny_info_list *)memAllocate(MEM_ACL_DENY_INFO_LIST);
    A->err_page_id = errorReservePageId(t);
    A->err_page_name = xstrdup(t);
    A->next = (acl_deny_info_list *) NULL;
    /* next expect a list of ACL names */
    Tail = &A->acl_list;

    while ((t = strtok(NULL, w_space))) {
        L = (acl_name_list *)memAllocate(MEM_ACL_NAME_LIST);
        xstrncpy(L->name, t, ACL_NAME_SZ);
        *Tail = L;
        Tail = &L->next;
    }

    if (A->acl_list == NULL) {
        debugs(28, 0, "aclParseDenyInfoLine: " << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, 0, "aclParseDenyInfoLine: deny_info line contains no ACL's, skipping");
        memFree(A, MEM_ACL_DENY_INFO_LIST);
        return;
    }

    for (B = *head, T = head; B; T = &B->next, B = B->next)

        ;	/* find the tail */
    *T = A;
}