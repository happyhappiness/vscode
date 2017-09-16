

	    name = ent->pw_name;

	}

	else

	    name = ap_user_name;



#ifndef OS2

	/* OS/2 dosen't support groups. */



	/* Reset `groups' attributes. */



	if (initgroups(name, ap_group_id) == -1) {

	    ap_log_error(APLOG_MARK, APLOG_ALERT, server_conf,

