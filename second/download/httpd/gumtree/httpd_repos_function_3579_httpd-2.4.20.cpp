static int hook_note_cookie_auth_failure(request_rec * r,
                                         const char *auth_type)
{
    if (strcasecmp(auth_type, "form"))
        return DECLINED;

    note_cookie_auth_failure(r);
    return OK;
}