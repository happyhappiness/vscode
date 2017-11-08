static void reportError(const char *msg, apr_status_t rv, 
                        apr_pool_t *pool)
{
    fprintf(stderr, "%s\n", msg);
    if (rv != APR_SUCCESS)
        fprintf(stderr, "Error: %d\n'%s'\n", rv,
                apr_psprintf(pool, "%pm", &rv));
    
}