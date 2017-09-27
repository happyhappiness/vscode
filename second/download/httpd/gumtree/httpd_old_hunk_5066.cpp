    }
    apr_pool_userdata_set(object, raw_key, NULL, r->server->process->pool);
    apr_thread_mutex_unlock(lua_ivm_mutex);
    return 0;
}

#define APLUA_REQ_TRACE(lev) static int req_trace##lev(lua_State *L)  \
{                                                               \
    return req_log_at(L, APLOG_TRACE##lev);                     \
}

APLUA_REQ_TRACE(1)
