static apr_status_t file_cache_el_final(cache_handle_t *h, request_rec *r)
{
    apr_status_t rv;
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config,
                                                 &disk_cache_module);
    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;

    /* move the data over */
    if (dobj->fd) {
        apr_file_flush(dobj->fd);
        if (!dobj->datafile) {
            dobj->datafile = data_file(r->pool, conf->dirlevels, conf->dirlength,
                                       conf->cache_root, h->cache_obj->key);
        }
        /* Remove old file with the same name. If remove fails, then
         * perhaps we need to create the directory tree where we are
         * about to write the new file.
         */
        rv = apr_file_remove(dobj->datafile, r->pool);
        if (rv != APR_SUCCESS) {
            mkdir_structure(conf, dobj->datafile, r->pool);
        }

        /*
         * This assumes that the tempfile is on the same file system
         * as the cache_root. If not, then we need a file copy/move
         * rather than a rename.
         */
        rv = apr_file_rename(dobj->tempfile, dobj->datafile, r->pool);
        if (rv != APR_SUCCESS) {
            /* XXX log */
        }

        apr_file_close(dobj->fd);
        dobj->fd = NULL;
       /* XXX log */
   }

   return APR_SUCCESS;
}