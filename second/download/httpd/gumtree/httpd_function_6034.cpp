apr_array_header_t *h2_push_diary_update(h2_session *session, apr_array_header_t *pushes)
{
    apr_array_header_t *npushes = pushes;
    h2_push_diary_entry e;
    int i, idx;
    
    if (session->push_diary && pushes) {
        npushes = NULL;
        
        for (i = 0; i < pushes->nelts; ++i) {
            h2_push *push;
            
            push = APR_ARRAY_IDX(pushes, i, h2_push*);
            session->push_diary->dcalc(session->push_diary, &e.hash, push);
            idx = h2_push_diary_find(session->push_diary, e.hash);
            if (idx >= 0) {
                /* Intentional no APLOGNO */
                ap_log_cerror(APLOG_MARK, GCSLOG_LEVEL, 0, session->c,
                              "push_diary_update: already there PUSH %s", push->req->path);
                move_to_last(session->push_diary, idx);
            }
            else {
                /* Intentional no APLOGNO */
                ap_log_cerror(APLOG_MARK, GCSLOG_LEVEL, 0, session->c,
                              "push_diary_update: adding PUSH %s", push->req->path);
                if (!npushes) {
                    npushes = apr_array_make(pushes->pool, 5, sizeof(h2_push_diary_entry*));
                }
                APR_ARRAY_PUSH(npushes, h2_push*) = push;
                h2_push_diary_append(session->push_diary, &e);
            }
        }
    }
    return npushes;
}