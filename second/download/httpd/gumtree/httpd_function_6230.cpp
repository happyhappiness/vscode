apr_status_t h2_session_set_prio(h2_session *session, h2_stream *stream, 
                                 const h2_priority *prio)
{
    apr_status_t status = APR_SUCCESS;
#ifdef H2_NG2_CHANGE_PRIO
    nghttp2_stream *s_grandpa, *s_parent, *s;
    
    if (prio == NULL) {
        /* we treat this as a NOP */
        return APR_SUCCESS;
    }
    s = nghttp2_session_find_stream(session->ngh2, stream->id);
    if (!s) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                      "h2_stream(%ld-%d): lookup of nghttp2_stream failed",
                      session->id, stream->id);
        return APR_EINVAL;
    }
    
    s_parent = nghttp2_stream_get_parent(s);
    if (s_parent) {
        nghttp2_priority_spec ps;
        int id_parent, id_grandpa, w_parent, w;
        int rv = 0;
        const char *ptype = "AFTER";
        h2_dependency dep = prio->dependency;
        
        id_parent = nghttp2_stream_get_stream_id(s_parent);
        s_grandpa = nghttp2_stream_get_parent(s_parent);
        if (s_grandpa) {
            id_grandpa = nghttp2_stream_get_stream_id(s_grandpa);
        }
        else {
            /* parent of parent does not exist, 
             * only possible if parent == root */
            dep = H2_DEPENDANT_AFTER;
        }
        
        switch (dep) {
            case H2_DEPENDANT_INTERLEAVED:
                /* PUSHed stream is to be interleaved with initiating stream.
                 * It is made a sibling of the initiating stream and gets a
                 * proportional weight [1, MAX_WEIGHT] of the initiaing
                 * stream weight.
                 */
                ptype = "INTERLEAVED";
                w_parent = nghttp2_stream_get_weight(s_parent);
                w = valid_weight(w_parent * ((float)prio->weight / NGHTTP2_MAX_WEIGHT));
                nghttp2_priority_spec_init(&ps, id_grandpa, w, 0);
                break;
                
            case H2_DEPENDANT_BEFORE:
                /* PUSHed stream os to be sent BEFORE the initiating stream.
                 * It gets the same weight as the initiating stream, replaces
                 * that stream in the dependency tree and has the initiating
                 * stream as child.
                 */
                ptype = "BEFORE";
                w = w_parent = nghttp2_stream_get_weight(s_parent);
                nghttp2_priority_spec_init(&ps, stream->id, w_parent, 0);
                id_grandpa = nghttp2_stream_get_stream_id(s_grandpa);
                rv = nghttp2_session_change_stream_priority(session->ngh2, id_parent, &ps);
                if (rv < 0) {
                    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03202)
                                  "h2_stream(%ld-%d): PUSH BEFORE, weight=%d, "
                                  "depends=%d, returned=%d",
                                  session->id, id_parent, ps.weight, ps.stream_id, rv);
                    return APR_EGENERAL;
                }
                nghttp2_priority_spec_init(&ps, id_grandpa, w, 0);
                break;
                
            case H2_DEPENDANT_AFTER:
                /* The PUSHed stream is to be sent after the initiating stream.
                 * Give if the specified weight and let it depend on the intiating
                 * stream.
                 */
                /* fall through, it's the default */
            default:
                nghttp2_priority_spec_init(&ps, id_parent, valid_weight(prio->weight), 0);
                break;
        }


        rv = nghttp2_session_change_stream_priority(session->ngh2, stream->id, &ps);
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03203)
                      "h2_stream(%ld-%d): PUSH %s, weight=%d, "
                      "depends=%d, returned=%d",
                      session->id, stream->id, ptype, 
                      ps.weight, ps.stream_id, rv);
        status = (rv < 0)? APR_EGENERAL : APR_SUCCESS;
    }
#else
    (void)session;
    (void)stream;
    (void)prio;
    (void)valid_weight;
#endif
    return status;
}