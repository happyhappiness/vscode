                ptype = "BEFORE";
                w = w_parent = nghttp2_stream_get_weight(s_parent);
                nghttp2_priority_spec_init(&ps, stream->id, w_parent, 0);
                id_grandpa = nghttp2_stream_get_stream_id(s_grandpa);
                rv = nghttp2_session_change_stream_priority(session->ngh2, id_parent, &ps);
                if (rv < 0) {
                    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                                  "h2_stream(%ld-%d): PUSH BEFORE2, weight=%d, "
                                  "depends=%d, returned=%d",
                                  session->id, id_parent, ps.weight, ps.stream_id, rv);
                    return APR_EGENERAL;
                }
                nghttp2_priority_spec_init(&ps, id_grandpa, w, 0);
                break;
