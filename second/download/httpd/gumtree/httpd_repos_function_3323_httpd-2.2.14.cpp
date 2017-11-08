static void reportError(const char *msg, apr_status_t rv, 
                        apr_pool_t *pool)
{
    fprintf(stderr, "%s\nError: %d\n'%s'\n", msg, rv,
            apr_psprintf(pool, "%pm", &rv));
}