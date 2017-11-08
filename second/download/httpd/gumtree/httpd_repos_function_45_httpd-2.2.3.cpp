static apr_status_t htdbm_valid_username(htdbm_t *htdbm)
{
    if (!htdbm->username || (strlen(htdbm->username) > 64) || (strlen(htdbm->username) < 1)) {
        fprintf(stderr, "Invalid username length\n");
        return APR_EINVAL;
    }
    if (strchr(htdbm->username, ':')) {
        fprintf(stderr, "Username contains invalid characters\n");
        return APR_EINVAL;
    }
    return APR_SUCCESS;
}