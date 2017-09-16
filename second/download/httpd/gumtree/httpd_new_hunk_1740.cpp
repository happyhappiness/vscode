{

    configfile_t *f;

    char l[MAX_STRING_LEN];

    const char *rpw, *w;



    if (!(f = ap_pcfg_openfile(r->pool, auth_pwfile))) {

	ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

		    "Could not open password file: %s", auth_pwfile);

	return NULL;

    }

    while (!(ap_cfg_getline(l, MAX_STRING_LEN, f))) {

	if ((l[0] == '#') || (!l[0]))

	    continue;

