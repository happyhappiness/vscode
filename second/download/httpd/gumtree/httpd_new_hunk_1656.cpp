                }
                /* AJP13_SEND_HEADERS: process them */
                status = ajp_parse_header(r, conf, conn->data);
                if (status != APR_SUCCESS) {
                    backend_failed = 1;
                }
                headers_sent = 1;
                break;
            case CMD_AJP13_SEND_BODY_CHUNK:
                /* AJP13_SEND_BODY_CHUNK: piece of data */
                status = ajp_parse_data(r, conn->data, &size, &send_body_chunk_buff);
                if (status == APR_SUCCESS) {
                    /* AJP13_SEND_BODY_CHUNK with zero length
                     * is explicit flush message
                     */
                    if (size == 0) {
                        if (headers_sent) {
                            e = apr_bucket_flush_create(r->connection->bucket_alloc);
