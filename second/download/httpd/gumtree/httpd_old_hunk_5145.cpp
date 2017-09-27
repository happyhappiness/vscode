
    /* Oh dear, no luck matching header to the body */
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00710)
            "Cached URL info header '%s' didn't match body, ignoring this entry",
            dobj->name);

    return DECLINED;
}

static void close_disk_cache_fd(disk_cache_file_t *file)
{
   if (file->fd != NULL) {
