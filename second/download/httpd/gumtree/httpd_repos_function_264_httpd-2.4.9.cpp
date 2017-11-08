static dav_error * dav_fs_walker(dav_fs_walker_context *fsctx, int depth)
{
    const dav_walk_params *params = fsctx->params;
    apr_pool_t *pool = params->pool;
    apr_status_t status;
    dav_error *err = NULL;
    int isdir = fsctx->res1.collection;
    apr_finfo_t dirent;
    apr_dir_t *dirp;

    /* ensure the context is prepared properly, then call the func */
    err = (*params->func)(&fsctx->wres,
                          isdir
                          ? DAV_CALLTYPE_COLLECTION
                          : DAV_CALLTYPE_MEMBER);
    if (err != NULL) {
        return err;
    }

    if (depth == 0 || !isdir) {
        return NULL;
    }

    /* put a trailing slash onto the directory, in preparation for appending
     * files to it as we discovery them within the directory */
    dav_check_bufsize(pool, &fsctx->path1, DAV_BUFFER_PAD);
    fsctx->path1.buf[fsctx->path1.cur_len++] = '/';
    fsctx->path1.buf[fsctx->path1.cur_len] = '\0';        /* in pad area */

    /* if a secondary path is present, then do that, too */
    if (fsctx->path2.buf != NULL) {
        dav_check_bufsize(pool, &fsctx->path2, DAV_BUFFER_PAD);
        fsctx->path2.buf[fsctx->path2.cur_len++] = '/';
        fsctx->path2.buf[fsctx->path2.cur_len] = '\0';        /* in pad area */
    }

    /* Note: the URI should ALREADY have a trailing "/" */

    /* for this first pass of files, all resources exist */
    fsctx->res1.exists = 1;

    /* a file is the default; we'll adjust if we hit a directory */
    fsctx->res1.collection = 0;
    fsctx->res2.collection = 0;

    /* open and scan the directory */
    if ((status = apr_dir_open(&dirp, fsctx->path1.buf, pool)) != APR_SUCCESS) {
        /* ### need a better error */
        return dav_new_error(pool, HTTP_NOT_FOUND, 0, status, NULL);
    }
    while ((apr_dir_read(&dirent, APR_FINFO_DIRENT, dirp)) == APR_SUCCESS) {
        apr_size_t len;
        apr_size_t escaped_len;

        len = strlen(dirent.name);

        /* avoid recursing into our current, parent, or state directories */
        if (dirent.name[0] == '.'
              && (len == 1 || (dirent.name[1] == '.' && len == 2))) {
            continue;
        }

        if (params->walk_type & DAV_WALKTYPE_AUTH) {
            /* ### need to authorize each file */
            /* ### example: .htaccess is normally configured to fail auth */

            /* stuff in the state directory and temp files are never authorized! */
            if (!strcmp(dirent.name, DAV_FS_STATE_DIR) ||
                !strncmp(dirent.name, DAV_FS_TMP_PREFIX,
                         strlen(DAV_FS_TMP_PREFIX))) {
                continue;
            }
        }
        /* skip the state dir and temp files unless a HIDDEN is performed */
        if (!(params->walk_type & DAV_WALKTYPE_HIDDEN)
            && (!strcmp(dirent.name, DAV_FS_STATE_DIR) ||
                !strncmp(dirent.name, DAV_FS_TMP_PREFIX,
                         strlen(DAV_FS_TMP_PREFIX)))) {
            continue;
        }

        /* append this file onto the path buffer (copy null term) */
        dav_buffer_place_mem(pool, &fsctx->path1, dirent.name, len + 1, 0);

        status = apr_stat(&fsctx->info1.finfo, fsctx->path1.buf,
                          DAV_FINFO_MASK, pool);
        if (status != APR_SUCCESS && status != APR_INCOMPLETE) {
            /* woah! where'd it go? */
            /* ### should have a better error here */
            err = dav_new_error(pool, HTTP_NOT_FOUND, 0, status, NULL);
            break;
        }

        /* copy the file to the URI, too. NOTE: we will pad an extra byte
           for the trailing slash later. */
        escaped_len = dav_fs_append_uri(pool, &fsctx->uri_buf, dirent.name, 1);

        /* if there is a secondary path, then do that, too */
        if (fsctx->path2.buf != NULL) {
            dav_buffer_place_mem(pool, &fsctx->path2, dirent.name, len + 1, 0);
        }

        /* set up the (internal) pathnames for the two resources */
        fsctx->info1.pathname = fsctx->path1.buf;
        fsctx->info2.pathname = fsctx->path2.buf;

        /* set up the URI for the current resource */
        fsctx->res1.uri = fsctx->uri_buf.buf;

        /* ### for now, only process regular files (e.g. skip symlinks) */
        if (fsctx->info1.finfo.filetype == APR_REG) {
            /* call the function for the specified dir + file */
            if ((err = (*params->func)(&fsctx->wres,
                                       DAV_CALLTYPE_MEMBER)) != NULL) {
                /* ### maybe add a higher-level description? */
                break;
            }
        }
        else if (fsctx->info1.finfo.filetype == APR_DIR) {
            apr_size_t save_path_len = fsctx->path1.cur_len;
            apr_size_t save_uri_len = fsctx->uri_buf.cur_len;
            apr_size_t save_path2_len = fsctx->path2.cur_len;

            /* adjust length to incorporate the subdir name */
            fsctx->path1.cur_len += len;
            fsctx->path2.cur_len += len;

            /* adjust URI length to incorporate subdir and a slash */
            fsctx->uri_buf.cur_len += escaped_len + 1;
            fsctx->uri_buf.buf[fsctx->uri_buf.cur_len - 1] = '/';
            fsctx->uri_buf.buf[fsctx->uri_buf.cur_len] = '\0';

            /* switch over to a collection */
            fsctx->res1.collection = 1;
            fsctx->res2.collection = 1;

            /* recurse on the subdir */
            /* ### don't always want to quit on error from single child */
            if ((err = dav_fs_walker(fsctx, depth - 1)) != NULL) {
                /* ### maybe add a higher-level description? */
                break;
            }

            /* put the various information back */
            fsctx->path1.cur_len = save_path_len;
            fsctx->path2.cur_len = save_path2_len;
            fsctx->uri_buf.cur_len = save_uri_len;

            fsctx->res1.collection = 0;
            fsctx->res2.collection = 0;

            /* assert: res1.exists == 1 */
        }
    }

    /* ### check the return value of this? */
    apr_dir_close(dirp);

    if (err != NULL)
        return err;

    if (params->walk_type & DAV_WALKTYPE_LOCKNULL) {
        apr_size_t offset = 0;

        /* null terminate the directory name */
        fsctx->path1.buf[fsctx->path1.cur_len - 1] = '\0';

        /* Include any lock null resources found in this collection */
        fsctx->res1.collection = 1;
        if ((err = dav_fs_get_locknull_members(&fsctx->res1,
                                               &fsctx->locknull_buf)) != NULL) {
            /* ### maybe add a higher-level description? */
            return err;
        }

        /* put a slash back on the end of the directory */
        fsctx->path1.buf[fsctx->path1.cur_len - 1] = '/';

        /* these are all non-existant (files) */
        fsctx->res1.exists = 0;
        fsctx->res1.collection = 0;
        memset(&fsctx->info1.finfo, 0, sizeof(fsctx->info1.finfo));

        while (offset < fsctx->locknull_buf.cur_len) {
            apr_size_t len = strlen(fsctx->locknull_buf.buf + offset);
            dav_lock *locks = NULL;

            /*
            ** Append the locknull file to the paths and the URI. Note that
            ** we don't have to pad the URI for a slash since a locknull
            ** resource is not a collection.
            */
            dav_buffer_place_mem(pool, &fsctx->path1,
                                 fsctx->locknull_buf.buf + offset, len + 1, 0);
            dav_fs_append_uri(pool, &fsctx->uri_buf,
                              fsctx->locknull_buf.buf + offset, 0);
            if (fsctx->path2.buf != NULL) {
                dav_buffer_place_mem(pool, &fsctx->path2,
                                     fsctx->locknull_buf.buf + offset,
                                     len + 1, 0);
            }

            /* set up the (internal) pathnames for the two resources */
            fsctx->info1.pathname = fsctx->path1.buf;
            fsctx->info2.pathname = fsctx->path2.buf;

            /* set up the URI for the current resource */
            fsctx->res1.uri = fsctx->uri_buf.buf;

            /*
            ** To prevent a PROPFIND showing an expired locknull
            ** resource, query the lock database to force removal
            ** of both the lock entry and .locknull, if necessary..
            ** Sure, the query in PROPFIND would do this.. after
            ** the locknull resource was already included in the
            ** return.
            **
            ** NOTE: we assume the caller has opened the lock database
            **       if they have provided DAV_WALKTYPE_LOCKNULL.
            */
            /* ### we should also look into opening it read-only and
               ### eliding timed-out items from the walk, yet leaving
               ### them in the locknull database until somebody opens
               ### the thing writable.
               */
            /* ### probably ought to use has_locks. note the problem
               ### mentioned above, though... we would traverse this as
               ### a locknull, but then a PROPFIND would load the lock
               ### info, causing a timeout and the locks would not be
               ### reported. Therefore, a null resource would be returned
               ### in the PROPFIND.
               ###
               ### alternative: just load unresolved locks. any direct
               ### locks will be timed out (correct). any indirect will
               ### not (correct; consider if a parent timed out -- the
               ### timeout routines do not walk and remove indirects;
               ### even the resolve func would probably fail when it
               ### tried to find a timed-out direct lock).
            */
            if ((err = dav_lock_query(params->lockdb, &fsctx->res1,
                                      &locks)) != NULL) {
                /* ### maybe add a higher-level description? */
                return err;
            }

            /* call the function for the specified dir + file */
            if (locks != NULL &&
                (err = (*params->func)(&fsctx->wres,
                                       DAV_CALLTYPE_LOCKNULL)) != NULL) {
                /* ### maybe add a higher-level description? */
                return err;
            }

            offset += len + 1;
        }

        /* reset the exists flag */
        fsctx->res1.exists = 1;
    }

    if (params->walk_type & DAV_WALKTYPE_POSTFIX) {
        /* replace the dirs' trailing slashes with null terms */
        fsctx->path1.buf[--fsctx->path1.cur_len] = '\0';
        fsctx->uri_buf.buf[--fsctx->uri_buf.cur_len] = '\0';
        if (fsctx->path2.buf != NULL) {
            fsctx->path2.buf[--fsctx->path2.cur_len] = '\0';
        }

        /* this is a collection which exists */
        fsctx->res1.collection = 1;

        return (*params->func)(&fsctx->wres, DAV_CALLTYPE_POSTFIX);
    }

    return NULL;
}