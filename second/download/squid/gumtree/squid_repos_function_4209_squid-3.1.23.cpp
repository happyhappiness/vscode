err_type
aclGetDenyInfoPage(acl_deny_info_list ** head, const char *name, int redirect_allowed)
{
    acl_deny_info_list *A = NULL;

    debugs(28, 8, HERE << "got called for " << name);

    for (A = *head; A; A = A->next) {
        acl_name_list *L = NULL;

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