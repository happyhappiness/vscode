static apr_status_t file_cache_errorcleanup(disk_cache_object_t *dobj, request_rec *r)
{
    /* Remove the header file and the body file. */
    apr_file_remove(dobj->hdrsfile, r->pool);
    apr_file_remove(dobj->datafile, r->pool);

    /* If we opened the temporary data file, close and remove it. */
    if (dobj->tfd) {
        apr_file_close(dobj->tfd);
        apr_file_remove(dobj->tempfile, r->pool);
        dobj->tfd = NULL;
    }

    return APR_SUCCESS;
}