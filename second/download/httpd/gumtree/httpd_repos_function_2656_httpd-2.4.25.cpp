apr_size_t h2_util_bl_print(char *buffer, apr_size_t bmax, 
                            const char *tag, const char *sep, 
                            h2_blist *bl)
{
    apr_size_t off = 0;
    const char *sp = "";
    apr_bucket *b;
    
    if (bl) {
        memset(buffer, 0, bmax--);
        off += apr_snprintf(buffer+off, bmax-off, "%s(", tag);
        for (b = H2_BLIST_FIRST(bl); 
             bmax && (b != H2_BLIST_SENTINEL(bl));
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