void ap_lua_load_apache2_lmodule(lua_State *L)
{
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "loaded");
    lua_newtable(L);
    lua_setfield(L, -2, "apache2");
    lua_setglobal(L, "apache2");
    lua_pop(L, 1);              /* empty stack */

    lua_getglobal(L, "apache2");

    lua_pushstring(L, ap_get_server_banner());
    lua_setfield(L, -2, "version");

    makeintegerfield(L, OK);
    makeintegerfield(L, DECLINED);
    makeintegerfield(L, DONE);
    makeintegerfield(L, HTTP_MOVED_TEMPORARILY);
    makeintegerfield(L, PROXYREQ_NONE);
    makeintegerfield(L, PROXYREQ_PROXY);
    makeintegerfield(L, PROXYREQ_REVERSE);
    makeintegerfield(L, PROXYREQ_RESPONSE);
    makeintegerfield(L, PROXYREQ_RESPONSE);
    makeintegerfield(L, AUTHZ_DENIED);
    makeintegerfield(L, AUTHZ_GRANTED);
    makeintegerfield(L, AUTHZ_NEUTRAL);
    makeintegerfield(L, AUTHZ_GENERAL_ERROR);
    makeintegerfield(L, AUTHZ_DENIED_NO_USER);
    
    /*
       makeintegerfield(L, HTTP_CONTINUE);
       makeintegerfield(L, HTTP_SWITCHING_PROTOCOLS);
       makeintegerfield(L, HTTP_PROCESSING);
       makeintegerfield(L, HTTP_OK);
       makeintegerfield(L, HTTP_CREATED);
       makeintegerfield(L, HTTP_ACCEPTED);
       makeintegerfield(L, HTTP_NON_AUTHORITATIVE);
       makeintegerfield(L, HTTP_NO_CONTENT);
       makeintegerfield(L, HTTP_RESET_CONTENT);
       makeintegerfield(L, HTTP_PARTIAL_CONTENT);
       makeintegerfield(L, HTTP_MULTI_STATUS);
       makeintegerfield(L, HTTP_ALREADY_REPORTED);
       makeintegerfield(L, HTTP_IM_USED);
       makeintegerfield(L, HTTP_MULTIPLE_CHOICES);
       makeintegerfield(L, HTTP_MOVED_PERMANENTLY);
       makeintegerfield(L, HTTP_MOVED_TEMPORARILY);
       makeintegerfield(L, HTTP_SEE_OTHER);
       makeintegerfield(L, HTTP_NOT_MODIFIED);
       makeintegerfield(L, HTTP_USE_PROXY);
       makeintegerfield(L, HTTP_TEMPORARY_REDIRECT);
       makeintegerfield(L, HTTP_PERMANENT_REDIRECT);
       makeintegerfield(L, HTTP_BAD_REQUEST);
       makeintegerfield(L, HTTP_UNAUTHORIZED);
       makeintegerfield(L, HTTP_PAYMENT_REQUIRED);
       makeintegerfield(L, HTTP_FORBIDDEN);
       makeintegerfield(L, HTTP_NOT_FOUND);
       makeintegerfield(L, HTTP_METHOD_NOT_ALLOWED);
       makeintegerfield(L, HTTP_NOT_ACCEPTABLE);
       makeintegerfield(L, HTTP_PROXY_AUTHENTICATION_REQUIRED);
       makeintegerfield(L, HTTP_REQUEST_TIME_OUT);
       makeintegerfield(L, HTTP_CONFLICT);
       makeintegerfield(L, HTTP_GONE);
       makeintegerfield(L, HTTP_LENGTH_REQUIRED);
       makeintegerfield(L, HTTP_PRECONDITION_FAILED);
       makeintegerfield(L, HTTP_REQUEST_ENTITY_TOO_LARGE);
       makeintegerfield(L, HTTP_REQUEST_URI_TOO_LARGE);
       makeintegerfield(L, HTTP_UNSUPPORTED_MEDIA_TYPE);
       makeintegerfield(L, HTTP_RANGE_NOT_SATISFIABLE);
       makeintegerfield(L, HTTP_EXPECTATION_FAILED);
       makeintegerfield(L, HTTP_UNPROCESSABLE_ENTITY);
       makeintegerfield(L, HTTP_LOCKED);
       makeintegerfield(L, HTTP_FAILED_DEPENDENCY);
       makeintegerfield(L, HTTP_UPGRADE_REQUIRED);
       makeintegerfield(L, HTTP_PRECONDITION_REQUIRED);
       makeintegerfield(L, HTTP_TOO_MANY_REQUESTS);
       makeintegerfield(L, HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE);
       makeintegerfield(L, HTTP_INTERNAL_SERVER_ERROR);
       makeintegerfield(L, HTTP_NOT_IMPLEMENTED);
       makeintegerfield(L, HTTP_BAD_GATEWAY);
       makeintegerfield(L, HTTP_SERVICE_UNAVAILABLE);
       makeintegerfield(L, HTTP_GATEWAY_TIME_OUT);
       makeintegerfield(L, HTTP_VERSION_NOT_SUPPORTED);
       makeintegerfield(L, HTTP_VARIANT_ALSO_VARIES);
       makeintegerfield(L, HTTP_INSUFFICIENT_STORAGE);
       makeintegerfield(L, HTTP_LOOP_DETECTED);
       makeintegerfield(L, HTTP_NOT_EXTENDED);
       makeintegerfield(L, HTTP_NETWORK_AUTHENTICATION_REQUIRED);
     */
}