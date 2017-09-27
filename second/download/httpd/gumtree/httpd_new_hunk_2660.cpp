        }

        /* We didn't get the magic bytes. */
        if (len != 10 ||
            deflate_hdr[0] != deflate_magic[0] ||
            deflate_hdr[1] != deflate_magic[1]) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01387) "Zlib: Invalid header");
            return APR_EGENERAL;
        }

        /* We can't handle flags for now. */
        if (deflate_hdr[3] != 0) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01388)
                          "Zlib: Unsupported flags %02x", (int)deflate_hdr[3]);
            return APR_EGENERAL;
        }

        zRC = inflateInit2(&ctx->stream, c->windowSize);

        if (zRC != Z_OK) {
            f->ctx = NULL;
            inflateEnd(&ctx->stream);
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01389)
                          "unable to init Zlib: "
                          "inflateInit2 returned %d: URL %s",
                          zRC, r->uri);
            ap_remove_input_filter(f);
            return ap_get_brigade(f->next, bb, mode, block, readbytes);
        }
