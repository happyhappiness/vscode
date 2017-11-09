apr_size_t h2_util_bucket_print(char *buffer, apr_size_t bmax, 
                                apr_bucket *b, const char *sep)
{
    apr_size_t off = 0;
    if (sep && *sep) {
        off += apr_snprintf(buffer+off, bmax-off, "%s", sep);
    }
    
    if (bmax <= off) {
        return off;
    }
    else if (APR_BUCKET_IS_METADATA(b)) {
        off += apr_snprintf(buffer+off, bmax-off, "%s", b->type->name);
    }
    else if (bmax > off) {
        off += apr_snprintf(buffer+off, bmax-off, "%s[%ld]", 
                            b->type->name, 
                            (long)(b->length == ((apr_size_t)-1)? 
                                   -1 : b->length));
    }
    return off;
}