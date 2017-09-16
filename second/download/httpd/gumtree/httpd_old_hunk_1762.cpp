	return log_scripterror(r, conf, FORBIDDEN, APLOG_NOERRNO,

			       "Options ExecCGI is off in this directory");

    if (nph && is_included)

	return log_scripterror(r, conf, FORBIDDEN, APLOG_NOERRNO,

			       "attempt to include NPH CGI script");



#if defined(__EMX__) || defined(WIN32)

    /* Allow for cgi files without the .EXE extension on them under OS/2 */

    if (r->finfo.st_mode == 0) {

	struct stat statbuf;



	r->filename = ap_pstrcat(r->pool, r->filename, ".EXE", NULL);



