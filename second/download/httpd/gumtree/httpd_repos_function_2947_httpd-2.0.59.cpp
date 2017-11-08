static apr_status_t test_safe_name(const char *name)
{
    /* Only accept ':' in the second position of the filename,
     * as the drive letter delimiter:
     */
    if (apr_isalpha(*name) && (name[1] == ':')) {
        name += 2;
    }
    while (*name) {
        if (!IS_FNCHAR(*name) && (*name != '\\') && (*name != '/')) {
            if (*name == '?' || *name == '*')
                return APR_EPATHWILD;
            else
                return APR_EBADPATH;
        }
        ++name;
    }
    return APR_SUCCESS;
}