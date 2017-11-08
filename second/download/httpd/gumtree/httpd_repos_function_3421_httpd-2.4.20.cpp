static int hook_note_basic_auth_failure(request_rec *r, const char *auth_type)
{
    if (strcasecmp(auth_type, "Basic"))
        return DECLINED;

    note_basic_auth_failure(r);
    return OK;
}