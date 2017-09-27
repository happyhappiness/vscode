log_scripterror(r, conf, HTTP_SERVICE_UNAVAILABLE, connect_errno, 
                                   apr_pstrcat(r->pool, APLOGNO(02833) "ScriptSock ", sockname, " does not exist", NULL));