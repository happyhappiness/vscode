dav_error * dav_lock_parse_lockinfo(request_rec *r,
				    const dav_resource *resource,
				    dav_lockdb *lockdb,
				    const apr_xml_doc *doc,
				    dav_lock **lock_request)
{
    apr_pool_t *p = r->pool;
    dav_error *err;
    apr_xml_elem *child;
    dav_lock *lock;

    if (!dav_validate_root(doc, "lockinfo")) {
	return dav_new_error(p, HTTP_BAD_REQUEST, 0,
			     "The request body contains an unexpected "
			     "XML root element.");
    }

    if ((err = (*lockdb->hooks->create_lock)(lockdb, resource,
                                             &lock)) != NULL) {
	return dav_push_error(p, err->status, 0,
			      "Could not parse the lockinfo due to an "
			      "internal problem creating a lock structure.",
			      err);
    }

    lock->depth = dav_get_depth(r, DAV_INFINITY);
    if (lock->depth == -1) {
	return dav_new_error(p, HTTP_BAD_REQUEST, 0,
			     "An invalid Depth header was specified.");
    }
    lock->timeout = dav_get_timeout(r);

    /* Parse elements in the XML body */
    for (child = doc->root->first_child; child; child = child->next) {
	if (strcmp(child->name, "locktype") == 0
	    && child->first_child
	    && lock->type == DAV_LOCKTYPE_UNKNOWN) {
	    if (strcmp(child->first_child->name, "write") == 0) {
		lock->type = DAV_LOCKTYPE_WRITE;
		continue;
	    }
	}
	if (strcmp(child->name, "lockscope") == 0
	    && child->first_child
	    && lock->scope == DAV_LOCKSCOPE_UNKNOWN) {
	    if (strcmp(child->first_child->name, "exclusive") == 0)
		lock->scope = DAV_LOCKSCOPE_EXCLUSIVE;
	    else if (strcmp(child->first_child->name, "shared") == 0)
		lock->scope = DAV_LOCKSCOPE_SHARED;
	    if (lock->scope != DAV_LOCKSCOPE_UNKNOWN)
		continue;
	}

	if (strcmp(child->name, "owner") == 0 && lock->owner == NULL) {
	    const char *text;

	    /* quote all the values in the <DAV:owner> element */
	    apr_xml_quote_elem(p, child);

	    /*
	    ** Store a full <DAV:owner> element with namespace definitions
	    ** and an xml:lang definition, if applicable.
	    */
	    apr_xml_to_text(p, child, APR_XML_X2T_FULL_NS_LANG, doc->namespaces, 
			    NULL, &text, NULL);
	    lock->owner = text;

	    continue;
	}

	return dav_new_error(p, HTTP_PRECONDITION_FAILED, 0,
			     apr_psprintf(p,
					 "The server cannot satisfy the "
					 "LOCK request due to an unknown XML "
					 "element (\"%s\") within the "
					 "DAV:lockinfo element.",
					 child->name));
    }

    *lock_request = lock;
    return NULL;
}