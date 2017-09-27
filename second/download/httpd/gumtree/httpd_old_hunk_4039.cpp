            /* If there is no data available, our session will automatically
             * suspend this stream and not ask for more data until we resume
             * it. Remember at our h2_stream that we need to do this.
             */
            nread = 0;
            h2_stream_set_suspended(stream, 1);
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                          "h2_stream(%ld-%d): suspending stream",
                          session->id, (int)stream_id);
            return NGHTTP2_ERR_DEFERRED;
            
        case APR_EOF:
            nread = 0;
            eos = 1;
            break;
            
        default:
            nread = 0;
            ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                          APLOGNO(02938) "h2_stream(%ld-%d): reading data",
                          session->id, (int)stream_id);
            return NGHTTP2_ERR_CALLBACK_FAILURE;
