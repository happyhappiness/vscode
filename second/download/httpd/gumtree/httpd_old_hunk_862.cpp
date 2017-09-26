    }

    if (r->server->path
        && !strncmp(r->uri, r->server->path, r->server->pathlen)
        && (r->server->path[r->server->pathlen - 1] == '/'
            || r->uri[r->server->pathlen] == '/'
            || r->uri[r->server->pathlen] == '\0')) 
    {
        /* skip all leading /'s (e.g. http://localhost///foo) 
         * so we are looking at only the relative path.
         */
        char *path = r->uri + r->server->pathlen;
        while (*path == '/') {
            ++path;
        }
        if (apr_filepath_merge(&r->filename, conf->ap_document_root, path,
                               APR_FILEPATH_TRUENAME
                             | APR_FILEPATH_SECUREROOT, r->pool)
                    != APR_SUCCESS) {
            return HTTP_FORBIDDEN;
        }
        r->canonical_filename = r->filename;
    }
    else {
        /*
         * Make sure that we do not mess up the translation by adding two
         * /'s in a row.  This happens under windows when the document
         * root ends with a /
         */
        /* skip all leading /'s (e.g. http://localhost///foo) 
         * so we are looking at only the relative path.
         */
        char *path = r->uri;
        while (*path == '/') {
            ++path;
        }
        if (apr_filepath_merge(&r->filename, conf->ap_document_root, path,
                               APR_FILEPATH_TRUENAME
                             | APR_FILEPATH_SECUREROOT, r->pool)
                    != APR_SUCCESS) {
            return HTTP_FORBIDDEN;
        }
        r->canonical_filename = r->filename;
    }

    return OK;
