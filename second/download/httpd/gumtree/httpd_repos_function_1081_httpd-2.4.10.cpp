void ap_lua_init_mutex(apr_pool_t *pool, server_rec *s) 
{
    apr_thread_mutex_create(&ap_lua_mutex, APR_THREAD_MUTEX_DEFAULT, pool);
}