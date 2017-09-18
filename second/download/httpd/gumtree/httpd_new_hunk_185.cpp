** |                                                       |
** +-------------------------------------------------------+
*/

#define REWRITELOCK_MODE ( APR_UREAD | APR_UWRITE | APR_GREAD | APR_WREAD )

static apr_status_t rewritelock_create(server_rec *s, apr_pool_t *p)
{
    apr_status_t rc;

    /* only operate if a lockfile is used */
    if (lockname == NULL || *(lockname) == '\0') {
        return APR_SUCCESS;
    }

    /* create the lockfile */
    rc = apr_global_mutex_create(&rewrite_mapr_lock_acquire, lockname,
                                 APR_LOCK_DEFAULT, p);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rc, s,
                     "mod_rewrite: Parent could not create RewriteLock "
                     "file %s", lockname);
        return rc;
    }

#if APR_USE_SYSVSEM_SERIALIZE
    rc = unixd_set_global_mutex_perms(rewrite_mapr_lock_acquire);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rc, s,
                     "mod_rewrite: Parent could not set permissions "
                     "on RewriteLock; check User and Group directives");
        return rc;
    }
#endif

    return APR_SUCCESS;
}

static apr_status_t rewritelock_remove(void *data)
{
    /* only operate if a lockfile is used */
    if (lockname == NULL || *(lockname) == '\0') {
