static const char *dav_generic_format_locktoken(apr_pool_t *p,
                                                const dav_locktoken *locktoken)
{
    char buf[APR_UUID_FORMATTED_LENGTH + 1];

    apr_uuid_format(buf, &locktoken->uuid);
    return apr_pstrcat(p, "opaquelocktoken:", buf, NULL);
}