    core_server_config *conf = ap_get_module_config(sconf, &core_module);

  

    if (r->proxyreq) {

        return HTTP_FORBIDDEN;

    }

    if ((r->uri[0] != '/') && strcmp(r->uri, "*")) {

	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

		     "Invalid URI in request %s", r->the_request);

	return BAD_REQUEST;

    }

    

    if (r->server->path 

	&& !strncmp(r->uri, r->server->path, r->server->pathlen)

