static dav_error * dav_generic_parse_locktoken(apr_pool_t *p,
                                               const char *char_token,
                                               dav_locktoken **locktoken_p)
{
    dav_locktoken *locktoken;

    if (ap_strstr_c(char_token, "opaquelocktoken:") != char_token) {
        return dav_new_error(p,
                             HTTP_BAD_REQUEST, DAV_ERR_LOCK_UNK_STATE_TOKEN, 0,
                             "The lock token uses an unknown State-token "
                             "format and could not be parsed.");
    }
    char_token += 16;

    locktoken = apr_pcalloc(p, sizeof(*locktoken));
    if (apr_uuid_parse(&locktoken->uuid, char_token)) {
        return dav_new_error(p, HTTP_BAD_REQUEST, DAV_ERR_LOCK_PARSE_TOKEN, 0,
                             "The opaquelocktoken has an incorrect format "
                             "and could not be parsed.");
    }

    *locktoken_p = locktoken;
    return NULL;
}