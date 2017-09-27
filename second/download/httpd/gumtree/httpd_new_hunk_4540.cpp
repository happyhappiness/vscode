    
    if (cache_digest && session->push_diary) {
        status = h2_push_diary_digest64_set(session->push_diary, req->authority, 
                                            cache_digest, stream->pool);
        if (status != APR_SUCCESS) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                          H2_SSSN_LOG(APLOGNO(03057), session,
                          "push diary set from Cache-Digest: %s"), cache_digest);
        }
    }
    pushes = h2_push_collect(stream->pool, req, stream->push_policy, res);
    return h2_push_diary_update(stream->session, pushes);
}

