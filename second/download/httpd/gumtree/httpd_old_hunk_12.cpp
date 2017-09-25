
            /* if we don't get the content-length, see if we have all the 
             * buckets and use their length to calculate the size 
             */
            apr_bucket *e;
            int all_buckets_here=0;
            size=0;
            APR_BRIGADE_FOREACH(e, in) {
                if (APR_BUCKET_IS_EOS(e)) {
                    all_buckets_here=1;
                    break;
                }
                if (APR_BUCKET_IS_FLUSH(e)) {
                    continue;
                }
                if (e->length < 0) {
                    break;
                }
                size += e->length;
            }

            if (!all_buckets_here) {
                size = -1;
            }
        }
    }

    /* It's safe to cache the response.
     *
