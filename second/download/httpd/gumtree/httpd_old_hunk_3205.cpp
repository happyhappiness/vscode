                dump_extn_value(bio, X509_EXTENSION_get_data(ext)) == 1) {
                BUF_MEM *buf;
                char **ptr = apr_array_push(array);
                BIO_get_mem_ptr(bio, &buf);
                *ptr = apr_pstrmemdup(p, buf->data, buf->length);
            } else {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                              "Found an extension '%s', but failed to "
                              "create a string from it", extension);
            }
            BIO_vfree(bio);
        }
    }
