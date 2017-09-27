            case CMD_AJP13_SEND_HEADERS:
                /* AJP13_SEND_HEADERS: process them */
                status = ajp_parse_header(r, conf, conn->data);
                if (status != APR_SUCCESS) {
                    backend_failed = 1;
                }
                break;
            case CMD_AJP13_SEND_BODY_CHUNK:
                /* AJP13_SEND_BODY_CHUNK: piece of data */
                status = ajp_parse_data(r, conn->data, &size, &buff);
                if (status == APR_SUCCESS) {
                    if (size == 0) {
                        /* AJP13_SEND_BODY_CHUNK with zero length
                         * is explicit flush message
                         */
                        e = apr_bucket_flush_create(r->connection->bucket_alloc);
                        APR_BRIGADE_INSERT_TAIL(output_brigade, e);
                    }
                    else {
                        e = apr_bucket_transient_create(buff, size,
                                                    r->connection->bucket_alloc);
                        APR_BRIGADE_INSERT_TAIL(output_brigade, e);

