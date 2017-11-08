dav_error * dav_validate_request(request_rec *r, dav_resource *resource,
				 int depth, dav_locktoken *locktoken,
				 dav_response **response, int flags,
                                 dav_lockdb *lockdb)
{
    dav_error *err;
    int result;
    dav_if_header *if_header;
    int lock_db_opened_locally = 0;
    const dav_hooks_locks *locks_hooks = DAV_GET_HOOKS_LOCKS(r);
    const dav_hooks_repository *repos_hooks = resource->hooks;
    dav_buffer work_buf = { 0 };
    dav_response *new_response;

#if DAV_DEBUG
    if (depth && response == NULL) {
	/*
	** ### bleck. we can't return errors for other URIs unless we have
        ** ### a "response" ptr.
	*/
	return dav_new_error(r->pool, HTTP_INTERNAL_SERVER_ERROR, 0,
			     "DESIGN ERROR: dav_validate_request called "
                             "with depth>0, but no response ptr.");
    }
#endif

    if (response != NULL)
	*response = NULL;

    /* Do the standard checks for conditional requests using 
     * If-..-Since, If-Match etc */
    if ((result = ap_meets_conditions(r)) != OK) {
	/* ### fix this up... how? */
	return dav_new_error(r->pool, result, 0, NULL);
    }

    /* always parse (and later process) the If: header */
    if ((err = dav_process_if_header(r, &if_header)) != NULL) {
	/* ### maybe add higher-level description */
	return err;
    }

    /* If a locktoken was specified, create a dummy if_header with which
     * to validate resources.  In the interim, figure out why DAV uses
     * locktokens in an if-header without a Lock-Token header to refresh
     * locks, but a Lock-Token header without an if-header to remove them.
     */
    if (locktoken != NULL) {
	dav_if_header *ifhdr_new;

	ifhdr_new = apr_pcalloc(r->pool, sizeof(*ifhdr_new));
	ifhdr_new->uri = resource->uri;
	ifhdr_new->uri_len = strlen(resource->uri);
	ifhdr_new->dummy_header = 1;

	ifhdr_new->state = apr_pcalloc(r->pool, sizeof(*ifhdr_new->state));
	ifhdr_new->state->type = dav_if_opaquelock;
	ifhdr_new->state->condition = DAV_IF_COND_NORMAL;
	ifhdr_new->state->locktoken = locktoken;

	ifhdr_new->next = if_header;
	if_header = ifhdr_new;
    }

    /*
    ** If necessary, open the lock database (read-only, lazily);
    ** the validation process may need to retrieve or update lock info.
    ** Otherwise, assume provided lockdb is valid and opened rw.
    */
    if (lockdb == NULL) {
        if (locks_hooks != NULL) {
            if ((err = (*locks_hooks->open_lockdb)(r, 0, 0, &lockdb)) != NULL) {
	        /* ### maybe insert higher-level comment */
	        return err;
            }
            lock_db_opened_locally = 1;
        }
    }

    /* (1) Validate the specified resource, at the specified depth */
    if (resource->exists && depth > 0) {
        dav_walker_ctx ctx = { { 0 } };
        dav_response *multi_status;

	ctx.w.walk_type = DAV_WALKTYPE_NORMAL;
	ctx.w.func = dav_validate_walker;
        ctx.w.walk_ctx = &ctx;
	ctx.w.pool = r->pool;
        ctx.w.root = resource;

	ctx.if_header = if_header;
	ctx.r = r;
        ctx.flags = flags;

	if (lockdb != NULL) {
	    ctx.w.lockdb = lockdb;
	    ctx.w.walk_type |= DAV_WALKTYPE_LOCKNULL;
	}

	err = (*repos_hooks->walk)(&ctx.w, DAV_INFINITY, &multi_status);
	if (err == NULL) {
            *response = multi_status;;
	}
        /* else: implies a 5xx status code occurred. */
    }
    else {
	err = dav_validate_resource_state(r->pool, resource, lockdb,
					  if_header, flags, &work_buf, r);
    }

    /* (2) Validate the parent resource if requested */
    if (err == NULL && (flags & DAV_VALIDATE_PARENT)) {
        dav_resource *parent_resource;

        err = (*repos_hooks->get_parent_resource)(resource, &parent_resource);

	if (err == NULL && parent_resource == NULL) {
	    err = dav_new_error(r->pool, HTTP_FORBIDDEN, 0,
				"Cannot access parent of repository root.");
	}
	else if (err == NULL) {
	    err = dav_validate_resource_state(r->pool, parent_resource, lockdb,
					      if_header,
                                              flags | DAV_VALIDATE_IS_PARENT,
                                              &work_buf, r);
	    
	    /*
	    ** This error occurred on the parent resource. This implies that
	    ** we have to create a multistatus response (to report the error
	    ** against a URI other than the Request-URI). "Convert" this error
	    ** into a multistatus response.
	    */
	    if (err != NULL) {
		new_response = apr_pcalloc(r->pool, sizeof(*new_response));
		
		new_response->href = parent_resource->uri;
		new_response->status = err->status;
		new_response->desc =
		    "A validation error has occurred on the parent resource, "
		    "preventing the operation on the resource specified by "
		    "the Request-URI.";
                if (err->desc != NULL) {
                    new_response->desc = apr_pstrcat(r->pool,
                                                    new_response->desc,
                                                    " The error was: ",
                                                    err->desc, NULL);
                }
		
		/* assert: DAV_VALIDATE_PARENT implies response != NULL */
		new_response->next = *response;
		*response = new_response;
		
		err = NULL;
	    }
	}
    }

    if (lock_db_opened_locally)
        (*locks_hooks->close_lockdb)(lockdb);

    /*
    ** If we don't have a (serious) error, and we have multistatus responses,
    ** then we need to construct an "error". This error will be the overall
    ** status returned, and the multistatus responses will go into its body.
    **
    ** For certain methods, the overall error will be a 424. The default is
    ** to construct a standard 207 response.
    */
    if (err == NULL && response != NULL && *response != NULL) {
        apr_text *propstat = NULL;

        if ((flags & DAV_VALIDATE_USE_424) != 0) {
            /* manufacture a 424 error to hold the multistatus response(s) */
            return dav_new_error(r->pool, HTTP_FAILED_DEPENDENCY, 0,
                                 "An error occurred on another resource, "
                                 "preventing the requested operation on "
                                 "this resource.");
        }

        /*
        ** Whatever caused the error, the Request-URI should have a 424
        ** associated with it since we cannot complete the method.
        **
        ** For a LOCK operation, insert an empty DAV:lockdiscovery property.
        ** For other methods, return a simple 424.
        */
        if ((flags & DAV_VALIDATE_ADD_LD) != 0) {
            propstat = apr_pcalloc(r->pool, sizeof(*propstat));
            propstat->text =
                "<D:propstat>" DEBUG_CR
                "<D:prop><D:lockdiscovery/></D:prop>" DEBUG_CR
                "<D:status>HTTP/1.1 424 Failed Dependency</D:status>" DEBUG_CR
                "</D:propstat>" DEBUG_CR;
        }

        /* create the 424 response */
        new_response = apr_pcalloc(r->pool, sizeof(*new_response));
        new_response->href = resource->uri;
        new_response->status = HTTP_FAILED_DEPENDENCY;
        new_response->propresult.propstats = propstat;
        new_response->desc =
            "An error occurred on another resource, preventing the "
            "requested operation on this resource.";

        new_response->next = *response;
        *response = new_response;

        /* manufacture a 207 error for the multistatus response(s) */
        return dav_new_error(r->pool, HTTP_MULTI_STATUS, 0,
                             "Error(s) occurred on resources during the "
                             "validation process.");
    }

    return err;
}