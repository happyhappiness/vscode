static void
parse_on_unsupported_protocol(acl_access **access)
{
    char *tm;
    if ((tm = ConfigParser::NextToken()) == NULL) {
        self_destruct();
        return;
    }

    allow_t action = allow_t(ACCESS_ALLOWED);
    if (strcmp(tm, "tunnel") == 0)
        action.kind = 1;
    else if (strcmp(tm, "respond") == 0)
        action.kind = 2;
    else {
        debugs(3, DBG_CRITICAL, "FATAL: unknown on_unsupported_protocol mode: " << tm);
        self_destruct();
        return;
    }

    // empty rule OK
    ParseAclWithAction(access, action, "on_unsupported_protocol");
}