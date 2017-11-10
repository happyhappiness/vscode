static void init_child(apr_pool_t *p, server_rec *s)
{
	/* Now register the last buffer flush with the cleanup engine */
    if (buffered_logs)
	    apr_pool_cleanup_register(p, s, flush_all_logs, flush_all_logs);
}