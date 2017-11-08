const char *dav_lock_get_activelock(request_rec *r, dav_lock *lock,
                                    dav_buffer *pbuf)
{
    dav_lock *lock_scan;
    const dav_hooks_locks *hooks = DAV_GET_HOOKS_LOCKS(r);
    int count = 0;
    dav_buffer work_buf = { 0 };
    apr_pool_t *p = r->pool;

    /* If no locks or no lock provider, there are no locks */
    if (lock == NULL || hooks == NULL) {
        /*
        ** Since resourcediscovery is defined with (activelock)*, 
        ** <D:activelock/> shouldn't be necessary for an empty lock.
        */
        return "";
    }

    /*
    ** Note: it could be interesting to sum the lengths of the owners
    **       and locktokens during this loop. However, the buffer
    **       mechanism provides some rough padding so that we don't
    **       really need to have an exact size. Further, constructing
    **       locktoken strings could be relatively expensive.
    */
    for (lock_scan = lock; lock_scan != NULL; lock_scan = lock_scan->next)
        count++;

    /* if a buffer was not provided, then use an internal buffer */
    if (pbuf == NULL)
        pbuf = &work_buf;

    /* reset the length before we start appending stuff */
    pbuf->cur_len = 0;

    /* prep the buffer with a "good" size */
    dav_check_bufsize(p, pbuf, count * 300);

    for (; lock != NULL; lock = lock->next) {
        char tmp[100];

#if DAV_DEBUG
        if (lock->rectype == DAV_LOCKREC_INDIRECT_PARTIAL) {
            /* ### crap. design error */
            dav_buffer_append(p, pbuf,
                              "DESIGN ERROR: attempted to product an "
                              "activelock element from a partial, indirect "
                              "lock record. Creating an XML parsing error "
                              "to ease detection of this situation: <");
        }
#endif

        dav_buffer_append(p, pbuf, "<D:activelock>" DEBUG_CR "<D:locktype>");
        switch (lock->type) {
        case DAV_LOCKTYPE_WRITE:
            dav_buffer_append(p, pbuf, "<D:write/>");
            break;
        default:
            /* ### internal error. log something? */
            break;
        }
        dav_buffer_append(p, pbuf, "</D:locktype>" DEBUG_CR "<D:lockscope>");
        switch (lock->scope) {
        case DAV_LOCKSCOPE_EXCLUSIVE:
            dav_buffer_append(p, pbuf, "<D:exclusive/>");
            break;
        case DAV_LOCKSCOPE_SHARED:
            dav_buffer_append(p, pbuf, "<D:shared/>");
            break;
        default:
            /* ### internal error. log something? */
            break;
        }
        dav_buffer_append(p, pbuf, "</D:lockscope>" DEBUG_CR);
        sprintf(tmp, "<D:depth>%s</D:depth>" DEBUG_CR,
                lock->depth == DAV_INFINITY ? "infinity" : "0");
        dav_buffer_append(p, pbuf, tmp);

        if (lock->owner) {
            /*
            ** This contains a complete, self-contained <DAV:owner> element,
            ** with namespace declarations and xml:lang handling. Just drop
            ** it in.
            */
            dav_buffer_append(p, pbuf, lock->owner);
        }
                
        dav_buffer_append(p, pbuf, "<D:timeout>");
        if (lock->timeout == DAV_TIMEOUT_INFINITE) {
            dav_buffer_append(p, pbuf, "Infinite");
        }
        else {
            time_t now = time(NULL);
            sprintf(tmp, "Second-%lu", (long unsigned int)(lock->timeout - now));
            dav_buffer_append(p, pbuf, tmp);
        }

        dav_buffer_append(p, pbuf,
                          "</D:timeout>" DEBUG_CR
                          "<D:locktoken>" DEBUG_CR
                          "<D:href>");
        dav_buffer_append(p, pbuf,
                          (*hooks->format_locktoken)(p, lock->locktoken));
        dav_buffer_append(p, pbuf,
                          "</D:href>" DEBUG_CR
                          "</D:locktoken>" DEBUG_CR
                          "</D:activelock>" DEBUG_CR);
    }

    return pbuf->buf;
}