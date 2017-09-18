    func(apr_psprintf(p, "total retrieves since starting: <b>%lu</b> hit, "
                     "<b>%lu</b> miss<br>", header->num_retrieves_hit,
                     header->num_retrieves_miss), arg);
    func(apr_psprintf(p, "total removes since starting: <b>%lu</b> hit, "
                     "<b>%lu</b> miss<br>", header->num_removes_hit,
                     header->num_removes_miss), arg);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, 
                 "leaving shmcb_status");
    return;
}

/*
**
** Memory manipulation and low-level cache operations 
