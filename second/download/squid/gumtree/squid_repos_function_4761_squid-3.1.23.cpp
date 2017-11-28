void
AuthUser::absorb (AuthUser *from)
{
    AuthUserRequest *auth_user_request;
    /*
     * XXX combine two authuser structs. Incomplete: it should merge
     * in hash references too and ask the module to merge in scheme
     * data
     */
    debugs(29, 5, "authenticateAuthUserMerge auth_user '" << from << "' into auth_user '" << this << "'.");
    dlink_node *link = from->requests.head;

    while (link) {
        auth_user_request = static_cast<AuthUserRequest *>(link->data);
        dlink_node *tmplink = link;
        link = link->next;
        dlinkDelete(tmplink, &from->requests);
        dlinkAddTail(auth_user_request, tmplink, &requests);
        auth_user_request->user(this);
    }

    references += from->references;
    from->references = 0;
    delete from;
}