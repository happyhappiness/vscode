    /* XXX FIXME we're referencing date on a path where we didn't set it */
    if (lastmod != APR_DATE_BAD && lastmod > date)
    {
        /* if its in the future, then replace by date */
        lastmod = date;
        lastmods = dates;
        ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, 
                     r->server,
                     "cache: Last modified is in the future, "
                     "replacing with now");
    }
    info->lastmod = lastmod;

