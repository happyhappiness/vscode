    NGH2_SET_CALLBACK(*pcb, send_data, on_send_data_cb);
    NGH2_SET_CALLBACK(*pcb, on_frame_send, on_frame_send_cb);

    return APR_SUCCESS;
}

static apr_status_t session_pool_cleanup(void *data)
{
    h2_session *session = data;
    
    /* keep us from destroying the pool, since that is already ongoing. */
    session->pool = NULL;
    h2_session_destroy(session);
    return APR_SUCCESS;
}

