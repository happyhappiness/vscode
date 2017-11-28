void
ProxyAuthLookup::LookupDone(void *data)
{
    ACLFilledChecklist *checklist = Filled(static_cast<ACLChecklist*>(data));

    if (checklist->auth_user_request == NULL || !checklist->auth_user_request->valid() || checklist->conn() == NULL) {
        /* credentials could not be checked either way
         * restart the whole process */
        /* OR the connection was closed, there's no way to continue */
        checklist->auth_user_request = NULL;

        if (checklist->conn() != NULL) {
            checklist->conn()->setAuth(NULL, "proxy_auth ACL failure");
        }
    }

    checklist->resumeNonBlockingCheck(ProxyAuthLookup::Instance());
}