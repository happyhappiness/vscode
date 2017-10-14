apr_bucket_file_create(fd, tf->Offset, (apr_size_t)fsize,
                                       r->pool, c->bucket_alloc);