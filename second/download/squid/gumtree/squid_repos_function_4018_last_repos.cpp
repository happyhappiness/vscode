err_type
aclGetDenyInfoPage(AclDenyInfoList ** head, const char *name, int redirect_allowed)
{
    if (!name) {
        debugs(28, 3, "ERR_NONE due to a NULL name");
        return ERR_NONE;
    }

    AclDenyInfoList *A = NULL;

    debugs(28, 8, HERE << "got called for " << name);

    for (A = *head; A; A = A->next) {
        AclNameList *L = NULL;

        if (!redirect_allowed && strchr(A->err_page_name, ':') ) {
            debugs(28, 8, HERE << "Skip '" << A->err_page_name << "' 30x redirects not allowed as response here.");
            continue;
        }

        for (L = A->acl_list; L; L = L->next) {
            if (!strcmp(name, L->name)) {
                debugs(28, 8, HERE << "match on " << name);
                return A->err_page_id;
            }

        }
    }

    debugs(28, 8, "aclGetDenyInfoPage: no match");
    return ERR_NONE;
}