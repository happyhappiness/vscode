
/**
 * Run the test_config function for each module; this hook is run
 * only if the server was invoked to test the configuration syntax.
 * @param pconf The config pool
 * @param s The list of server_recs
 */
AP_DECLARE_HOOK(void,test_config,(apr_pool_t *pconf, server_rec *s))

/**
 * Run the post_config function for each module
 * @param pconf The config pool
