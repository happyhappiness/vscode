static apr_status_t getpwnam_safe(const char *username,
                                  struct passwd *pw,
                                  char pwbuf[PWBUF_SIZE])
{
    struct passwd *pwptr;
#if APR_HAS_THREADS && defined(_POSIX_THREAD_SAFE_FUNCTIONS) && defined(HAVE_GETPWNAM_R)
    apr_status_t rv;

    /* POSIX defines getpwnam_r() et al to return the error number
     * rather than set errno, and requires pwptr to be set to NULL if
     * the entry is not found, imply that "not found" is not an error
     * condition; some implementations do return 0 with pwptr set to
     * NULL. */
    rv = getpwnam_r(username, pw, pwbuf, PWBUF_SIZE, &pwptr);
    if (rv) {
        return rv;
    }
    if (pwptr == NULL) {
        return APR_ENOENT;
    }
#else
    /* Some platforms (e.g. FreeBSD 4.x) do not set errno on NULL "not
     * found" return values for the non-threadsafe function either. */
    errno = 0;
    if ((pwptr = getpwnam(username)) != NULL) {
        memcpy(pw, pwptr, sizeof *pw);
    }
    else {
        return errno ? errno : APR_ENOENT;
    }
#endif
    return APR_SUCCESS;
}