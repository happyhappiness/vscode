        apr_size_t length;
        apr_bucket_read(e, &str, &length, APR_BLOCK_READ);
        apr_file_write(dobj->fd, str, &length);
    }
    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(b))) {
        file_cache_el_final(h, r);    /* Link to the perm file, and close the descriptor  */
        ap_log_error(APLOG_MARK, APLOG_INFO|APLOG_NOERRNO, 0, r->server,
                     "disk_cache: Cached body for URL %s",  dobj->name);
    }

    return APR_SUCCESS;	
}

