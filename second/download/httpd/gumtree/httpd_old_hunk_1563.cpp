    DBT d, q;
    char *pw = NULL;

    q.data = user;
    q.size = strlen(q.data);

    if (!(f = dbopen(auth_dbpwfile, O_RDONLY, 0664, DB_HASH, NULL))) {
	ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
		    "could not open db auth file: %s", auth_dbpwfile);
	return NULL;
    }

    if (!((f->get) (f, &q, &d, 0))) {
	pw = ap_palloc(r->pool, d.size + 1);
	strncpy(pw, d.data, d.size);
	pw[d.size] = '\0';	/* Terminate the string */
    }

    (f->close) (f);
    return pw;
}

/* We do something strange with the group file.  If the group file
 * contains any : we assume the format is
 *      key=username value=":"groupname [":"anything here is ignored]
