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
            off += apr_snprintf(buffer+off, bmax-off, "%s", b->type->name);
        }
    }
    else {
        const char *btype = b->type->name;
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