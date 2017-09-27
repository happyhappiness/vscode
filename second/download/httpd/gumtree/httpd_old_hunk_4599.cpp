        apr_sha1_final(digest, &sha1);
        encoded_len = apr_base64_encode_len(APR_SHA1_DIGESTSIZE);
        if (encoded_len) {
            encoded = apr_palloc(r->pool, encoded_len);
            encoded_len = apr_base64_encode(encoded, (char*) digest, APR_SHA1_DIGESTSIZE);
            r->status = 101;
            apr_table_set(r->headers_out, "Upgrade", "websocket");
            apr_table_set(r->headers_out, "Connection", "Upgrade");
            apr_table_set(r->headers_out, "Sec-WebSocket-Accept", encoded);
            
            /* Trick httpd into NOT using the chunked filter, IMPORTANT!!!111*/
            apr_table_set(r->headers_out, "Transfer-Encoding", "chunked");
            
            r->clength = 0;
            r->bytes_sent = 0;
            r->read_chunked = 0;
            ap_rflush(r);
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03012) 
