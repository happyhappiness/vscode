            if (b->length > remain) {
                apr_bucket_split(b, remain);
                if (io->slen == 0) {
                    /* complete write_size bucket, append unchanged */
                    APR_BUCKET_REMOVE(b);
                    APR_BRIGADE_INSERT_TAIL(io->output, b);
                    continue;
                }
            }
            else {
                /* bucket fits in remain, copy to scratch */
                status = read_to_scratch(io, b);
