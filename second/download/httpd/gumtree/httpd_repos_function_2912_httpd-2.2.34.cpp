static void dbd_oracle_init(apr_pool_t *pool)
{
    if (dbd_oracle_env == NULL) {
        /* Sadly, OCI_SHARED seems to be impossible to use, due to
         * various Oracle bugs.  See, for example, Oracle MetaLink bug 2972890
         * and PHP bug http://bugs.php.net/bug.php?id=23733
         */
#ifdef OCI_NEW_LENGTH_SEMANTICS
        OCIEnvCreate(&dbd_oracle_env, OCI_THREADED|OCI_NEW_LENGTH_SEMANTICS,
                     NULL, NULL, NULL, NULL, 0, NULL);
#else
        OCIEnvCreate(&dbd_oracle_env, OCI_THREADED,
                     NULL, NULL, NULL, NULL, 0, NULL);
#endif
    }
}