#define AP_LUA_MODULE_EXT ".so"
#endif
#endif

#if APR_HAS_THREADS
    apr_thread_mutex_t *ap_lua_mutex;
    
void ap_lua_init_mutex(apr_pool_t *pool, server_rec *s) 
{
    apr_thread_mutex_create(&ap_lua_mutex, APR_THREAD_MUTEX_DEFAULT, pool);
}
#endif

/* forward dec'l from this file */

#if 0
static void pstack_dump(lua_State *L, apr_pool_t *r, int level,
                        const char *msg)
