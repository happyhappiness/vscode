
        zRC = inflateInit2(&ctx->stream, c->windowSize);

        if (zRC != Z_OK) {
            f->ctx = NULL;
            inflateEnd(&ctx->stream);
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01397)
                          "unable to init Zlib: "
                          "inflateInit2 returned %d: URL %s",
                          zRC, r->uri);
            /*
             * Remove ourselves as it does not make sense to return:
             * We are not able to init libz and pass data down the chain
