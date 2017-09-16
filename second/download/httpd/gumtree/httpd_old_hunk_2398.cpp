static int log_scripterror(request_rec *r, cgi_server_conf * conf, int ret,

			   int show_errno, char *error)

{

    FILE *f;

    struct stat finfo;



    ap_log_error(APLOG_MARK, show_errno|APLOG_ERR, r->server, 

		"%s: %s", error, r->filename);



    if (!conf->logname ||

	((stat(ap_server_root_relative(r->pool, conf->logname), &finfo) == 0)

	 &&   (finfo.st_size > conf->logbytes)) ||

         ((f = ap_pfopen(r->pool, ap_server_root_relative(r->pool, conf->logname),

