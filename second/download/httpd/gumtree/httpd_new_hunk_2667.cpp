        /* read */
        apr_bucket_read(e, &data, &len, APR_BLOCK_READ);

        /* first bucket contains zlib header */
        if (!ctx->inflate_init++) {
            if (len < 10) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01403)
                              "Insufficient data for inflate");
                return APR_EGENERAL;
            }
            else  {
                zlib_method = data[2];
                zlib_flags = data[3];
                if (zlib_method != Z_DEFLATED) {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01404)
                                  "inflate: data not deflated!");
                    ap_remove_output_filter(f);
                    return ap_pass_brigade(f->next, bb);
                }
                if (data[0] != deflate_magic[0] ||
                    data[1] != deflate_magic[1] ||
                    (zlib_flags & RESERVED) != 0) {
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01405)
                                      "inflate: bad header");
                    return APR_EGENERAL ;
                }
                data += 10 ;
                len -= 10 ;
           }
           if (zlib_flags & EXTRA_FIELD) {
               unsigned int bytes = (unsigned int)(data[0]);
               bytes += ((unsigned int)(data[1])) << 8;
               bytes += 2;
               if (len < bytes) {
                   ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01406)
                                 "inflate: extra field too big (not "
                                 "supported)");
                   return APR_EGENERAL;
               }
               data += bytes;
               len -= bytes;
