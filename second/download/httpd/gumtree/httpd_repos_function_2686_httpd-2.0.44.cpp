static apr_status_t getpwnam_safe(const char *username,
                                  struct passwd *pw,
                                  char pwbuf[PWBUF_SIZE])
{
    struct passwd *pwptr;
#if APR_HAS_THREADS && defined(_POSIX_THREAD_SAFE_FUNCTIONS) && defined(HAVE_GETPWNAM_R)
    /* IRIX getpwnam_r() returns 0 and sets pwptr to NULL on failure */
    if (!getpwnam_r(username, pw, pwbuf, PWBUF_SIZE, &pwptr) && pwptr) {
        /* nothing extra to do on success */
#else
    if ((pwptr = getpwnam(username)) != NULL) {
        memcpy(pw, pwptr, sizeof *pw);
#endif
    }
    else {
        if (errno == 0) {
            /* this can happen with getpwnam() on FreeBSD 4.3 */
            return APR_EGENERAL;
        }
        return errno;
    }
    return APR_SUCCESS;
}

APR_DECLARE(apr_status_t) apr_uid_homepath_get(char **dirname,
                                               const char *username,
                                               apr_pool_t *p)
{
    struct passwd pw;
    char pwbuf[PWBUF_SIZE];
    apr_status_t rv;

    if ((rv = getpwnam_safe(username, &pw, pwbuf)) != APR_SUCCESS)
        return rv;

#ifdef OS2
    /* Need to manually add user name for OS/2 */
    *dirname = apr_pstrcat(p, pw.pw_dir, pw.pw_name, NULL);
#else
    *dirname = apr_pstrdup(p, pw.pw_dir);
#endif
    return APR_SUCCESS;
}



APR_DECLARE(apr_status_t) apr_uid_current(apr_uid_t *uid,
                                          apr_gid_t *gid,
                                          apr_pool_t *p)
{
    *uid = getuid();
    *gid = getgid();
  
    return APR_SUCCESS;
}




APR_DECLARE(apr_status_t) apr_uid_get(apr_uid_t *uid, apr_gid_t *gid,
                                      const char *username, apr_pool_t *p)
{
    struct passwd pw;
    char pwbuf[PWBUF_SIZE];
    apr_status_t rv;
        
    if ((rv = getpwnam_safe(username, &pw, pwbuf)) != APR_SUCCESS)
        return rv;

    *uid = pw.pw_uid;
    *gid = pw.pw_gid;

    return APR_SUCCESS;
}

APR_DECLARE(apr_status_t) apr_uid_name_get(char **username, apr_uid_t userid,
                                           apr_pool_t *p)
{
    struct passwd *pw;
#if APR_HAS_THREADS && defined(_POSIX_THREAD_SAFE_FUNCTIONS) && defined(HAVE_GETPWUID_R)
    struct passwd pwd;
    char pwbuf[PWBUF_SIZE];

    if (getpwuid_r(userid, &pwd, pwbuf, sizeof(pwbuf), &pw)) {
#else
    if ((pw = getpwuid(userid)) == NULL) {
#endif
        return errno;
    }
    *username = apr_pstrdup(p, pw->pw_name);
    return APR_SUCCESS;
}

/* deprecated */  
APR_DECLARE(apr_status_t) apr_get_home_directory(char **dirname,
                                                 const char *username,
                                                 apr_pool_t *p)
{
    return apr_uid_homepath_get(dirname, username, p);
}

/* deprecated */
APR_DECLARE(apr_status_t) apr_get_userid(apr_uid_t *uid, apr_gid_t *gid,
                                         const char *username, apr_pool_t *p)
{
    return apr_uid_get(uid, gid, username, p);
}

/* deprecated */
APR_DECLARE(apr_status_t) apr_current_userid(apr_uid_t *uid,
                                             apr_gid_t *gid,
                                             apr_pool_t *p)
{
    return apr_uid_current(uid, gid, p);
}

/* deprecated */
APR_DECLARE(apr_status_t) apr_get_username(char **username, apr_uid_t userid, 
                                           apr_pool_t *p)
{
    return apr_uid_name_get(username, userid, p);
}