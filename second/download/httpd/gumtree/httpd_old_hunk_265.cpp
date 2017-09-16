	return ap_pstrcat(cmd->pool, "Expected ", cmd->end_token, " but saw ",

	    cmd->cmd->name, NULL);

    }

    return cmd->end_token;

}



static const char *dirsection (cmd_parms *cmd, void *dummy, const char *arg)

{

    const char *errmsg;

    char *endp = strrchr (arg, '>');

    int old_overrides = cmd->override;

    char *old_path = cmd->path;

    core_dir_config *conf;

    void *new_dir_conf = ap_create_per_dir_config (cmd->pool);

    regex_t *r = NULL;

    const char *old_end_token;

    const command_rec *thiscmd = cmd->cmd;



    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);

    if (err != NULL) return err;



    if (endp) *endp = '\0';



    cmd->path = ap_getword_conf (cmd->pool, &arg);

#ifdef __EMX__

    /* Fix OS/2 HPFS filename case problem. */

    cmd->path = strlwr(cmd->path);

#endif    

    cmd->override = OR_ALL|ACCESS_CONF;



    if (thiscmd->cmd_data) { /* <DirectoryMatch> */

	r = ap_pregcomp(cmd->pool, cmd->path, REG_EXTENDED|USE_ICASE);

    }

    else if (!strcmp(cmd->path, "~")) {

	cmd->path = ap_getword_conf (cmd->pool, &arg);

	r = ap_pregcomp(cmd->pool, cmd->path, REG_EXTENDED|USE_ICASE);

    }

    else {

	/* Ensure that the pathname is canonical */

	cmd->path = ap_os_canonical_filename(cmd->pool, cmd->path);

    }



    old_end_token = cmd->end_token;

    cmd->end_token = thiscmd->cmd_data ? end_directorymatch_section : end_directory_section;

    errmsg = ap_srm_command_loop (cmd, new_dir_conf);

    if (errmsg == NULL) {

	errmsg = missing_endsection(cmd, 1);

    }

    cmd->end_token = old_end_token;

    if (errmsg != (thiscmd->cmd_data ? end_directorymatch_section : end_directory_section))

	return errmsg;



    conf = (core_dir_config *)ap_get_module_config(new_dir_conf, &core_module);

    conf->r = r;



    ap_add_per_dir_conf (cmd->server, new_dir_conf);



    if (*arg != '\0')

	return ap_pstrcat (cmd->pool, "Multiple ", thiscmd->name,

			"> arguments not (yet) supported.", NULL);



    cmd->path = old_path;

    cmd->override = old_overrides;



    return NULL;

}



static const char *urlsection (cmd_parms *cmd, void *dummy, const char *arg)

{

    const char *errmsg;

    char *endp = strrchr (arg, '>');

    int old_overrides = cmd->override;

    char *old_path = cmd->path;

    core_dir_config *conf;

    regex_t *r = NULL;

    const char *old_end_token;

    const command_rec *thiscmd = cmd->cmd;



    void *new_url_conf = ap_create_per_dir_config (cmd->pool);



    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);

    if (err != NULL) return err;



    if (endp) *endp = '\0';



    cmd->path = ap_getword_conf (cmd->pool, &arg);

    cmd->override = OR_ALL|ACCESS_CONF;



    if (thiscmd->cmd_data) { /* <LocationMatch> */

	r = ap_pregcomp(cmd->pool, cmd->path, REG_EXTENDED);

    }

    else if (!strcmp(cmd->path, "~")) {

	cmd->path = ap_getword_conf (cmd->pool, &arg);

	r = ap_pregcomp(cmd->pool, cmd->path, REG_EXTENDED);

    }



    old_end_token = cmd->end_token;

    cmd->end_token = thiscmd->cmd_data ? end_locationmatch_section : end_location_section;

    errmsg = ap_srm_command_loop (cmd, new_url_conf);

    if (errmsg == NULL) {

	errmsg = missing_endsection(cmd, 1);

    }

    cmd->end_token = old_end_token;

    if (errmsg != (thiscmd->cmd_data ? end_locationmatch_section : end_location_section))

	return errmsg;



    conf = (core_dir_config *)ap_get_module_config(new_url_conf, &core_module);

    conf->d = ap_pstrdup(cmd->pool, cmd->path);	/* No mangling, please */

    conf->d_is_fnmatch = ap_is_fnmatch( conf->d ) != 0;

    conf->r = r;



    ap_add_per_url_conf (cmd->server, new_url_conf);

    

    if (*arg != '\0')

	return ap_pstrcat (cmd->pool, "Multiple ", thiscmd->name,

			"> arguments not (yet) supported.", NULL);



    cmd->path = old_path;

    cmd->override = old_overrides;



    return NULL;

}



static const char *filesection (cmd_parms *cmd, core_dir_config *c, const char *arg)

{

    const char *errmsg;

    char *endp = strrchr (arg, '>');

    int old_overrides = cmd->override;

    char *old_path = cmd->path;

    core_dir_config *conf;

    regex_t *r = NULL;

    const char *old_end_token;

    const command_rec *thiscmd = cmd->cmd;



    void *new_file_conf = ap_create_per_dir_config (cmd->pool);



    const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT | NOT_IN_LOCATION);

    if (err != NULL) return err;



    if (endp) *endp = '\0';



    cmd->path = ap_getword_conf (cmd->pool, &arg);

    /* Only if not an .htaccess file */

    if (!old_path)

	cmd->override = OR_ALL|ACCESS_CONF;



    if (thiscmd->cmd_data) { /* <FilesMatch> */

        r = ap_pregcomp(cmd->pool, cmd->path, REG_EXTENDED|USE_ICASE);

    }

    else if (!strcmp(cmd->path, "~")) {

	cmd->path = ap_getword_conf (cmd->pool, &arg);

	r = ap_pregcomp(cmd->pool, cmd->path, REG_EXTENDED|USE_ICASE);

    }

    else {

	/* Ensure that the pathname is canonical */

	cmd->path = ap_os_canonical_filename(cmd->pool, cmd->path);

    }



    old_end_token = cmd->end_token;

    cmd->end_token = thiscmd->cmd_data ? end_filesmatch_section : end_files_section;

    errmsg = ap_srm_command_loop (cmd, new_file_conf);

    if (errmsg == NULL) {

	errmsg = missing_endsection(cmd, 1);

    }

    cmd->end_token = old_end_token;

    if (errmsg != (thiscmd->cmd_data ? end_filesmatch_section : end_files_section))

	return errmsg;



    conf = (core_dir_config *)ap_get_module_config(new_file_conf, &core_module);

    conf->d = cmd->path;

    conf->d_is_fnmatch = ap_is_fnmatch(conf->d) != 0;

    conf->r = r;



    add_file_conf (c, new_file_conf);



    if (*arg != '\0')

	return ap_pstrcat (cmd->pool, "Multiple ", thiscmd->name,

			"> arguments not (yet) supported.", NULL);



    cmd->path = old_path;

    cmd->override = old_overrides;



    return NULL;

}



/* XXX: NB: Currently, we have no way of checking

 * whether <IfModule> sections are closed properly.

 * Extra (redundant, unpaired) </IfModule> directives are

 * simply silently ignored.

 */

static const char *end_ifmod (cmd_parms *cmd, void *dummy) {

    return NULL;

}



static const char *start_ifmod (cmd_parms *cmd, void *dummy, char *arg)

{

    char *endp = strrchr (arg, '>');

    char l[MAX_STRING_LEN];

    int not = (arg[0] == '!');

    module *found;

    int nest = 1;



    if (endp) *endp = '\0';

    if (not) arg++;



    found = ap_find_linked_module(arg);



    if ((!not && found) || (not && !found))

      return NULL;



    while (nest && !(ap_cfg_getline (l, MAX_STRING_LEN, cmd->config_file))) {

        if (!strncasecmp(l, "<IfModule", 9))

	  nest++;

	if (!strcasecmp(l, "</IfModule>"))

	  nest--;

    }



    if (nest) {

	cmd->end_token = end_ifmodule_section;

	return missing_endsection(cmd, nest);

    }

    return NULL;

}



/* httpd.conf commands... beginning with the <VirtualHost> business */



static const char *virtualhost_section (cmd_parms *cmd, void *dummy, char *arg)

{

    server_rec *main_server = cmd->server, *s;

    const char *errmsg;

    char *endp = strrchr (arg, '>');

    pool *p = cmd->pool, *ptemp = cmd->temp_pool;

    const char *old_end_token;



    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) return err;



    if (endp) *endp = '\0';

    

    /* FIXME: There's another feature waiting to happen here -- since you

	can now put multiple addresses/names on a single <VirtualHost>

	you might want to use it to group common definitions and then

	define other "subhosts" with their individual differences.  But

	personally I'd rather just do it with a macro preprocessor. -djg */

    if (main_server->is_virtual)

	return "<VirtualHost> doesn't nest!";

    

    errmsg = ap_init_virtual_host (p, arg, main_server, &s);

    if (errmsg)

	return errmsg;



    s->next = main_server->next;

    main_server->next = s;



    s->defn_name = cmd->config_file->name;

    s->defn_line_number = cmd->config_file->line_number;



    old_end_token = cmd->end_token;

    cmd->end_token = end_virtualhost_section;

    cmd->server = s;

    errmsg = ap_srm_command_loop (cmd, s->lookup_defaults);

    cmd->server = main_server;

    if (errmsg == NULL) {

	errmsg = missing_endsection(cmd, 1);

    }

    cmd->end_token = old_end_token;



    if (s->srm_confname)

	ap_process_resource_config (s, s->srm_confname, p, ptemp);



    if (s->access_confname)

	ap_process_resource_config (s, s->access_confname, p, ptemp);

    

    if (errmsg == end_virtualhost_section)

	return NULL;

    return errmsg;

}



static const char *set_server_alias(cmd_parms *cmd, void *dummy, const char *arg)

{

    if (!cmd->server->names)

	return "ServerAlias only used in <VirtualHost>";

    while (*arg) {

	char **item, *name = ap_getword_conf(cmd->pool, &arg);

	if (ap_is_matchexp(name))

	    item = (char **) ap_push_array(cmd->server->wild_names);

	else

	    item = (char **) ap_push_array(cmd->server->names);

	*item = name;

    }

    return NULL;

}



static const char *add_module_command (cmd_parms *cmd, void *dummy, char *arg)

{

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) return err;



    if (!ap_add_named_module(arg))

	return ap_pstrcat(cmd->pool, "Cannot add module via name '", arg, 

			  "': not in list of loaded modules", NULL);

    return NULL;

}



static const char *clear_module_list_command (cmd_parms *cmd, void *dummy)

{

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) return err;



    ap_clear_module_list ();

    return NULL;

}



static const char *set_server_string_slot (cmd_parms *cmd, void *dummy,

		                                   char *arg)

{

    /* This one's pretty generic... */

  

    int offset = (int)(long)cmd->info;

    char *struct_ptr = (char *)cmd->server;

    

    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);

    if (err != NULL) return err;



    *(char **)(struct_ptr + offset) = arg;

    return NULL;

}



static const char *server_type (cmd_parms *cmd, void *dummy, char *arg)

{

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) return err;



    if (!strcasecmp (arg, "inetd")) ap_standalone = 0;

    else if (!strcasecmp (arg, "standalone")) ap_standalone = 1;

    else return "ServerType must be either 'inetd' or 'standalone'";



    return NULL;

}



static const char *server_port (cmd_parms *cmd, void *dummy, char *arg)

{

    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);

    int port;



    if (err != NULL) 

	return err;

    port = atoi(arg);

    if (port <= 0 || port >= 65536) /* 65536 == 1<<16 */

	return ap_pstrcat(cmd->temp_pool, "The port number \"", arg, 

		       "\" is outside the appropriate range (i.e. 1..65535).",

		       NULL);

    cmd->server->port = port;

    return NULL;

}



static const char *set_signature_flag (cmd_parms *cmd, core_dir_config *d, 

		                               char *arg)

{

    const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT);

    if (err != NULL) return err;



    if (strcasecmp(arg, "On") == 0)

	d->server_signature = srv_sig_on;

    else if (strcasecmp(arg, "Off") == 0)

	d->server_signature = srv_sig_off;

    else if (strcasecmp(arg, "EMail") == 0)

	d->server_signature = srv_sig_withmail;

    else

	return "ServerSignature: use one of: off | on | email";

    return NULL;

}



static const char *set_send_buffer_size (cmd_parms *cmd, void *dummy, char *arg)

{

    int s = atoi (arg);

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) return err;



    if (s < 512 && s != 0) {

        return "SendBufferSize must be >= 512 bytes, or 0 for system default.";

    }

    cmd->server->send_buffer_size = s;

    return NULL;

}



static const char *set_user (cmd_parms *cmd, void *dummy, char *arg)

{

    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);

    if (err != NULL) return err;



    if (!cmd->server->is_virtual) {

	ap_user_name = arg;

	cmd->server->server_uid = ap_user_id = ap_uname2id(arg);

    }

    else {

	if (ap_suexec_enabled)

	    cmd->server->server_uid = ap_uname2id(arg);

	else {

	    cmd->server->server_uid = ap_user_id;

	    fprintf(stderr,

		"Warning: User directive in <VirtualHost> "

		"requires SUEXEC wrapper.\n");

	}

    }

#if !defined (BIG_SECURITY_HOLE) && !defined (__EMX__)

    if (cmd->server->server_uid == 0) {

	fprintf (stderr,

"Error:\tApache has not been designed to serve pages while running\n"

"\tas root.  There are known race conditions that will allow any\n"

"\tlocal user to read any file on the system.  Should you still\n"

"\tdesire to serve pages as root then add -DBIG_SECURITY_HOLE to\n"

"\tthe EXTRA_CFLAGS line in your src/Configuration file and rebuild\n"

"\tthe server.  It is strongly suggested that you instead modify the\n"

"\tUser directive in your httpd.conf file to list a non-root user.\n");

	exit (1);

    }

#endif



    return NULL;

}



static const char *set_group (cmd_parms *cmd, void *dummy, char *arg)

{

    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);

    if (err != NULL) return err;



    if (!cmd->server->is_virtual)

	cmd->server->server_gid = ap_group_id = ap_gname2id(arg);

    else {

	if (ap_suexec_enabled)

	    cmd->server->server_gid = ap_gname2id(arg);

	else {

	    cmd->server->server_gid = ap_group_id;

	    fprintf(stderr,

		    "Warning: Group directive in <VirtualHost> requires SUEXEC wrapper.\n");

	}

    }



    return NULL;

}



static const char *set_server_root (cmd_parms *cmd, void *dummy, char *arg) 

{

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) return err;



    if (!ap_is_directory (arg)) return "ServerRoot must be a valid directory";

    ap_cpystrn (ap_server_root, ap_os_canonical_filename(cmd->pool, arg), sizeof(ap_server_root));

    return NULL;

}



static const char *set_timeout (cmd_parms *cmd, void *dummy, char *arg) {

    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);

    if (err != NULL) return err;



    cmd->server->timeout = atoi (arg);

    return NULL;

}



static const char *set_keep_alive_timeout (cmd_parms *cmd, void *dummy,

		                                   char *arg)

{

    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);

    if (err != NULL) return err;



    cmd->server->keep_alive_timeout = atoi (arg);

    return NULL;

}



static const char *set_keep_alive (cmd_parms *cmd, void *dummy, char *arg) 

{

    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);

    if (err != NULL) return err;



    /* We've changed it to On/Off, but used to use numbers

     * so we accept anything but "Off" or "0" as "On"

     */

    if (!strcasecmp(arg, "off") || !strcmp(arg, "0"))

	cmd->server->keep_alive = 0;

    else

	cmd->server->keep_alive = 1;

    return NULL;

}



static const char *set_keep_alive_max (cmd_parms *cmd, void *dummy, char *arg) 

{

    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);

    if (err != NULL) return err;



    cmd->server->keep_alive_max = atoi (arg);

    return NULL;

}



static const char *set_pidfile (cmd_parms *cmd, void *dummy, char *arg) 

{

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) return err;



    if (cmd->server->is_virtual)

	return "PidFile directive not allowed in <VirtualHost>";

    ap_pid_fname = arg;

    return NULL;

}



static const char *set_scoreboard (cmd_parms *cmd, void *dummy, char *arg) 

{

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) return err;



    ap_scoreboard_fname = arg;

    return NULL;

}



static const char *set_lockfile (cmd_parms *cmd, void *dummy, char *arg) 

{

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) return err;



    ap_lock_fname = arg;

    return NULL;

}



static const char *set_idcheck (cmd_parms *cmd, core_dir_config *d, int arg) 

{

    const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT);

    if (err != NULL) return err;



    d->do_rfc1413 = arg != 0;

    return NULL;

}



static const char *set_hostname_lookups (cmd_parms *cmd, core_dir_config *d,

		                                 char *arg)

{

    const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT);

    if (err != NULL) return err;



    if (!strcasecmp (arg, "on")) {

	d->hostname_lookups = HOSTNAME_LOOKUP_ON;

    } else if (!strcasecmp (arg, "off")) {

	d->hostname_lookups = HOSTNAME_LOOKUP_OFF;

    } else if (!strcasecmp (arg, "double")) {

	d->hostname_lookups = HOSTNAME_LOOKUP_DOUBLE;

    } else {

	return "parameter must be 'on', 'off', or 'double'";

    }

    return NULL;

}



static const char *set_serverpath (cmd_parms *cmd, void *dummy, char *arg) 

{

    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);

    if (err != NULL) return err;



    cmd->server->path = arg;

    cmd->server->pathlen = strlen (arg);

    return NULL;

}



static const char *set_content_md5 (cmd_parms *cmd, core_dir_config *d, int arg) 

{

    const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT);

    if (err != NULL) return err;



    d->content_md5 = arg != 0;

    return NULL;

}



static const char *set_use_canonical_name (cmd_parms *cmd, core_dir_config *d, 

		                                   int arg)

{

    const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT);



    if (err != NULL)

	return err;

    

    d->use_canonical_name = arg != 0;

    return NULL;

}



static const char *set_daemons_to_start (cmd_parms *cmd, void *dummy, char *arg) 

{

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) return err;



    ap_daemons_to_start = atoi (arg);

    return NULL;

}



static const char *set_min_free_servers (cmd_parms *cmd, void *dummy, char *arg) 

{

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) return err;



    ap_daemons_min_free = atoi (arg);

    if (ap_daemons_min_free <= 0) {

       fprintf(stderr, "WARNING: detected MinSpareServers set to non-positive.\n");

       fprintf(stderr, "Resetting to 1 to avoid almost certain Apache failure.\n");

       fprintf(stderr, "Please read the documentation.\n");

       ap_daemons_min_free = 1;

    }

       

    return NULL;

}



static const char *set_max_free_servers (cmd_parms *cmd, void *dummy, char *arg) 

{

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) return err;



    ap_daemons_max_free = atoi (arg);

    return NULL;

}



static const char *set_server_limit (cmd_parms *cmd, void *dummy, char *arg) 

{

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) return err;



    ap_daemons_limit = atoi (arg);

    if (ap_daemons_limit > HARD_SERVER_LIMIT) {

       fprintf(stderr, "WARNING: MaxClients of %d exceeds compile time limit "

           "of %d servers,\n", ap_daemons_limit, HARD_SERVER_LIMIT);

       fprintf(stderr, " lowering MaxClients to %d.  To increase, please "

           "see the\n", HARD_SERVER_LIMIT);

       fprintf(stderr, " HARD_SERVER_LIMIT define in src/httpd.h.\n");

       ap_daemons_limit = HARD_SERVER_LIMIT;

    } else if (ap_daemons_limit < 1) {

	fprintf (stderr, "WARNING: Require MaxClients > 0, setting to 1\n");

	ap_daemons_limit = 1;

    }

    return NULL;

}



static const char *set_max_requests (cmd_parms *cmd, void *dummy, char *arg) 

{

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) return err;



    ap_max_requests_per_child = atoi (arg);

    return NULL;

}



static const char *set_threads (cmd_parms *cmd, void *dummy, char *arg) {

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) return err;



    ap_threads_per_child = atoi (arg);

#ifdef WIN32

    if(ap_threads_per_child > 64)

	return "Can't have more than 64 threads in Windows (for now)";

#endif



    return NULL;

}



static const char *set_excess_requests (cmd_parms *cmd, void *dummy, char *arg) 

{

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) return err;



    ap_excess_requests_per_child = atoi (arg);

    return NULL;

}





#if defined(RLIMIT_CPU) || defined(RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined(RLIMIT_NPROC) || defined(RLIMIT_AS)

static void set_rlimit(cmd_parms *cmd, struct rlimit **plimit, const char *arg,

                       const char * arg2, int type)

{

    char *str;

    struct rlimit *limit;

    /* If your platform doesn't define rlim_t then typedef it in conf.h */

    rlim_t cur = 0;

    rlim_t max = 0;



    *plimit = (struct rlimit *)ap_pcalloc(cmd->pool,sizeof **plimit);

    limit = *plimit;

    if ((getrlimit(type, limit)) != 0)	{

	*plimit = NULL;

	ap_log_error(APLOG_MARK, APLOG_ERR, cmd->server,

		    "%s: getrlimit failed", cmd->cmd->name);

	return;

    }



    if ((str = ap_getword_conf(cmd->pool, &arg))) {

	if (!strcasecmp(str, "max")) {

	    cur = limit->rlim_max;

