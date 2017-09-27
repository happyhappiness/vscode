    if (status == APR_SUCCESS && !*peos && !*plen) {
        return APR_EAGAIN;
    }
    return status;
}

apr_size_t h2_util_bucket_print(char *buffer, apr_size_t bmax, 
                                apr_bucket *b, const char *sep)
{
    apr_size_t off = 0;
    if (sep && *sep) {
        off += apr_snprintf(buffer+off, bmax-off, "%s", sep);
    }
    
    if (APR_BUCKET_IS_METADATA(b)) {
        if (APR_BUCKET_IS_EOS(b)) {
            off += apr_snprintf(buffer+off, bmax-off, "eos");
        }
        else if (APR_BUCKET_IS_FLUSH(b)) {
            off += apr_snprintf(buffer+off, bmax-off, "flush");
        }
        else if (AP_BUCKET_IS_EOR(b)) {
            off += apr_snprintf(buffer+off, bmax-off, "eor");
        }
        else {
            off += apr_snprintf(buffer+off, bmax-off, "meta(unknown)");
        }
    }
    else {
        const char *btype = "data";
        if (APR_BUCKET_IS_FILE(b)) {
            btype = "file";
        }
        else if (APR_BUCKET_IS_PIPE(b)) {
            btype = "pipe";
        }
        else if (APR_BUCKET_IS_SOCKET(b)) {
            btype = "socket";
        }
        else if (APR_BUCKET_IS_HEAP(b)) {
            btype = "heap";
        }
        else if (APR_BUCKET_IS_TRANSIENT(b)) {
            btype = "transient";
        }
        else if (APR_BUCKET_IS_IMMORTAL(b)) {
            btype = "immortal";
        }
#if APR_HAS_MMAP
        else if (APR_BUCKET_IS_MMAP(b)) {
            btype = "mmap";
        }
#endif
        else if (APR_BUCKET_IS_POOL(b)) {
            btype = "pool";
        }
        
        off += apr_snprintf(buffer+off, bmax-off, "%s[%ld]", 
                            btype, 
                            (long)(b->length == ((apr_size_t)-1)? 
                                   -1 : b->length));
    }
    return off;
}

apr_size_t h2_util_bb_print(char *buffer, apr_size_t bmax, 
                            const char *tag, const char *sep, 
                            apr_bucket_brigade *bb)
{
    apr_size_t off = 0;
    const char *sp = "";
    apr_bucket *b;
    
    if (bb) {
        memset(buffer, 0, bmax--);
        off += apr_snprintf(buffer+off, bmax-off, "%s(", tag);
        for (b = APR_BRIGADE_FIRST(bb); 
             bmax && (b != APR_BRIGADE_SENTINEL(bb));
             b = APR_BUCKET_NEXT(b)) {
            
            off += h2_util_bucket_print(buffer+off, bmax-off, b, sp);
            sp = " ";
        }
        off += apr_snprintf(buffer+off, bmax-off, ")%s", sep);
    }
    else {
        off += apr_snprintf(buffer+off, bmax-off, "%s(null)%s", tag, sep);
    }
    return off;
}

apr_status_t h2_append_brigade(apr_bucket_brigade *to,
                               apr_bucket_brigade *from, 
                               apr_off_t *plen,
                               int *peos)
