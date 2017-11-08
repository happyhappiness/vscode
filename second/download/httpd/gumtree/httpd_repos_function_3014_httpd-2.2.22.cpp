static void dbd_mysql_init(apr_pool_t *pool)
{
    my_init();
    mysql_thread_init();

    /* FIXME: this is a guess; find out what it really does */
    apr_pool_cleanup_register(pool, NULL, thread_end, apr_pool_cleanup_null);
}