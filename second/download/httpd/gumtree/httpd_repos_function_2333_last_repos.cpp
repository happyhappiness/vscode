apr_size_t h2_util_bb_print(char *buffer, apr_size_t bmax, 
                            const char *tag, const char *sep, 
                            apr_bucket_brigade *bb)
{
    apr_size_t off = 0;
    const char *sp = "";
    apr_bucket *b;
    
    if (bmax > 1) {
        if (bb) {
            memset(buffer, 0, bmax--);
            off += apr_snprintf(buffer+off, bmax-off, "%s(", tag);
            for (b = APR_BRIGADE_FIRST(bb); 
                 (bmax > off) && (b != APR_BRIGADE_SENTINEL(bb));
                 b = APR_BUCKET_NEXT(b)) {
                
                off += h2_util_bucket_print(buffer+off, bmax-off, b, sp);
                sp = " ";
            }
            if (bmax > off) {
                off += apr_snprintf(buffer+off, bmax-off, ")%s", sep);
            }
        }
        else {
            off += apr_snprintf(buffer+off, bmax-off, "%s(null)%s", tag, sep);
        }
    }
    return off;
}