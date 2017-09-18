    else
	m->nospflag = 0;
    strncpy(m->desc, l, sizeof(m->desc) - 1);
    m->desc[sizeof(m->desc) - 1] = '\0';

#if MIME_MAGIC_DEBUG
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, serv,
		MODNAME ": parse line=%d m=%x next=%x cont=%d desc=%s",
		lineno, m, m->next, m->cont_level, m->desc);
#endif /* MIME_MAGIC_DEBUG */

    return 0;
}
