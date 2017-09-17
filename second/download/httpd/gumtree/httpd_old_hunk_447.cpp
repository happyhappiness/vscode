	else {
	    cur = atol(str);
	}
    }
    else {
	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, cmd->server,
		    "Invalid parameters for %s", cmd->cmd->name);
	return;
    }
    
    if (arg2 && (str = ap_getword_conf(cmd->pool, &arg2)))
	max = atol(str);

    /* if we aren't running as root, cannot increase max */
    if (geteuid()) {
	limit->rlim_cur = cur;
	if (max)
	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, cmd->server,
			"Must be uid 0 to raise maximum %s", cmd->cmd->name);
    }
    else {
	if (cur)
	    limit->rlim_cur = cur;
	if (max)
	    limit->rlim_max = max;
    }
}
#endif

#if !defined (RLIMIT_CPU) || !(defined (RLIMIT_DATA) || defined (RLIMIT_VMEM) || defined(RLIMIT_AS)) || !defined (RLIMIT_NPROC)
static const char *no_set_limit (cmd_parms *cmd, core_dir_config *conf,
				 char *arg, char *arg2)
{
    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, cmd->server,
		"%s not supported on this platform", cmd->cmd->name);
    return NULL;
}
#endif

#ifdef RLIMIT_CPU
static const char *set_limit_cpu (cmd_parms *cmd, core_dir_config *conf, 
	                          char *arg, char *arg2)
{
    set_rlimit(cmd,&conf->limit_cpu,arg,arg2,RLIMIT_CPU);
    return NULL;
}
#endif

#if defined (RLIMIT_DATA) || defined (RLIMIT_VMEM) || defined(RLIMIT_AS)
static const char *set_limit_mem (cmd_parms *cmd, core_dir_config *conf, 
	                          char *arg, char * arg2)
{
#if defined(RLIMIT_AS)
    set_rlimit(cmd,&conf->limit_mem,arg,arg2,RLIMIT_AS);
#elif defined(RLIMIT_DATA)
    set_rlimit(cmd,&conf->limit_mem,arg,arg2,RLIMIT_DATA);
#elif defined(RLIMIT_VMEM)
    set_rlimit(cmd,&conf->limit_mem,arg,arg2,RLIMIT_VMEM);
#endif
    return NULL;
}
#endif

#ifdef RLIMIT_NPROC
static const char *set_limit_nproc (cmd_parms *cmd, core_dir_config *conf,  
	                            char *arg, char * arg2)
{
    set_rlimit(cmd,&conf->limit_nproc,arg,arg2,RLIMIT_NPROC);
    return NULL;
}
#endif

static const char *set_bind_address (cmd_parms *cmd, void *dummy, char *arg) 
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) return err;

    ap_bind_address.s_addr = ap_get_virthost_addr (arg, NULL);
    return NULL;
}

static const char *set_listener(cmd_parms *cmd, void *dummy, char *ips)
{
    listen_rec *new;
    char *ports;
    unsigned short port;

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) return err;

    ports=strchr(ips, ':');
    if (ports != NULL)
    {
	if (ports == ips) return "Missing IP address";
	else if (ports[1] == '\0')
	    return "Address must end in :<port-number>";
	*(ports++) = '\0';
    } else
	ports = ips;

    new=ap_pcalloc(cmd->pool, sizeof(listen_rec));
    new->local_addr.sin_family = AF_INET;
    if (ports == ips) /* no address */
	new->local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    else
	new->local_addr.sin_addr.s_addr = ap_get_virthost_addr(ips, NULL);
    port=atoi(ports);
    if(!port)
	return "Port must be numeric";
    new->local_addr.sin_port = htons(port);
    new->fd = -1;
    new->used = 0;
    new->next = ap_listeners;
    ap_listeners = new;
    return NULL;
}

static const char *set_listenbacklog (cmd_parms *cmd, void *dummy, char *arg) 
{
    int b;

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) return err;

    b = atoi (arg);
    if (b < 1) return "ListenBacklog must be > 0";
    ap_listenbacklog = b;
    return NULL;
}

static const char *set_coredumpdir (cmd_parms *cmd, void *dummy, char *arg) 
{
    struct stat finfo;
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) return err;

    arg = ap_server_root_relative(cmd->pool, arg);
    if ((stat(arg, &finfo) == -1) || !S_ISDIR(finfo.st_mode)) {
	return ap_pstrcat(cmd->pool, "CoreDumpDirectory ", arg, 
	    " does not exist or is not a directory", NULL);
    }
    ap_cpystrn(ap_coredump_dir, arg, sizeof(ap_coredump_dir));
    return NULL;
}

static const char *include_config (cmd_parms *cmd, void *dummy, char *name)
