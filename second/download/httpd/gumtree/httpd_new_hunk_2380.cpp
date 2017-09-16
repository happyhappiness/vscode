    DBT d, q;

    char *pw = NULL;



    q.data = user;

    q.size = strlen(q.data);



#ifdef DB2

    if (db_open(auth_dbpwfile, DB_HASH, O_RDONLY, 0664, NULL, NULL,  &f) != 0) {

#else

    if (!(f = dbopen(auth_dbpwfile, O_RDONLY, 0664, DB_HASH, NULL))) {

#endif

	ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

		    "could not open db auth file: %s", auth_dbpwfile);

	return NULL;

    }



#ifdef DB2

    if (!((f->get) (f, NULL, &q, &d, 0))) {

#else

    if (!((f->get) (f, &q, &d, 0))) {

#endif

	pw = ap_palloc(r->pool, d.size + 1);

	strncpy(pw, d.data, d.size);

	pw[d.size] = '\0';	/* Terminate the string */

    }



#ifdef DB2

    (f->close) (f, 0);

#else

    (f->close) (f);

#endif

    return pw;

}



/* We do something strange with the group file.  If the group file

 * contains any : we assume the format is

 *      key=username value=":"groupname [":"anything here is ignored]

