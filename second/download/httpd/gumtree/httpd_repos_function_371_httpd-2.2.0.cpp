static dav_error * dav_insert_coreprop(dav_propdb *propdb,
                                       int propid, const char *name,
                                       dav_prop_insert what,
                                       apr_text_header *phdr,
                                       dav_prop_insert *inserted)
{
    const char *value = NULL;
    dav_error *err;

    *inserted = DAV_PROP_INSERT_NOTDEF;

    /* fast-path the common case */
    if (propid == DAV_PROPID_CORE_UNKNOWN)
        return NULL;

    switch (propid) {

    case DAV_PROPID_CORE_lockdiscovery:
        if (propdb->lockdb != NULL) {
            dav_lock *locks;

            if ((err = dav_lock_query(propdb->lockdb, propdb->resource,
                                      &locks)) != NULL) {
                return dav_push_error(propdb->p, err->status, 0,
                                      "DAV:lockdiscovery could not be "
                                      "determined due to a problem fetching "
                                      "the locks for this resource.",
                                      err);
            }

            /* fast-path the no-locks case */
            if (locks == NULL) {
                value = "";
            }
            else {
                /*
                ** This may modify the buffer. value may point to
                ** wb_lock.pbuf or a string constant.
                */
                value = dav_lock_get_activelock(propdb->r, locks,
                                                &propdb->wb_lock);

                /* make a copy to isolate it from changes to wb_lock */
                value = apr_pstrdup(propdb->p, propdb->wb_lock.buf);
            }
        }
        break;

    case DAV_PROPID_CORE_supportedlock:
        if (propdb->lockdb != NULL) {
            value = (*propdb->lockdb->hooks->get_supportedlock)(propdb->resource);
        }
        break;

    case DAV_PROPID_CORE_getcontenttype:
        if (propdb->subreq == NULL) {
            dav_do_prop_subreq(propdb);
        }
        if (propdb->subreq->content_type != NULL) {
            value = propdb->subreq->content_type;
        }
        break;

    case DAV_PROPID_CORE_getcontentlanguage:
    {
        const char *lang;

        if (propdb->subreq == NULL) {
            dav_do_prop_subreq(propdb);
        }
        if ((lang = apr_table_get(propdb->subreq->headers_out,
                                 "Content-Language")) != NULL) {
            value = lang;
        }
        break;
    }

    default:
        /* fall through to interpret as a dead property */
        break;
    }

    /* if something was supplied, then insert it */
    if (value != NULL) {
        const char *s;

        if (what == DAV_PROP_INSERT_SUPPORTED) {
            /* use D: prefix to refer to the DAV: namespace URI,
             * and let the namespace attribute default to "DAV:"
             */
            s = apr_psprintf(propdb->p,
                            "<D:supported-live-property D:name=\"%s\"/>" DEBUG_CR,
                            name);
        }
        else if (what == DAV_PROP_INSERT_VALUE && *value != '\0') {
            /* use D: prefix to refer to the DAV: namespace URI */
            s = apr_psprintf(propdb->p, "<D:%s>%s</D:%s>" DEBUG_CR,
                            name, value, name);
        }
        else {
            /* use D: prefix to refer to the DAV: namespace URI */
            s = apr_psprintf(propdb->p, "<D:%s/>" DEBUG_CR, name);
        }
        apr_text_append(propdb->p, phdr, s);

        *inserted = what;
    }

    return NULL;
}