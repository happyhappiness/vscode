#ifdef LOG_LOCAL6
	{ LOG_LOCAL6, "local6" },
#endif
#ifdef LOG_LOCAL7
	{ LOG_LOCAL7, "local7" },
#endif
	{ -1, NULL }};


/* note that we do not initialise the defaults union - it is not allowed in ANSI C */
static struct parm_struct parm_table[] =
{
 {"address",           P_STRING, P_GLOBAL,&Globals.bind_address,       NULL,0},
 {"motd file",         P_STRING, P_GLOBAL,&Globals.motd_file,          NULL,0},
 {"pid file",          P_STRING, P_GLOBAL,&Globals.pid_file,           NULL,0},
 {"port",              P_INTEGER,P_GLOBAL,&Globals.rsync_port,         NULL,0},
 {"socket options",    P_STRING, P_GLOBAL,&Globals.socket_options,     NULL,0},

 {"auth users",        P_STRING, P_LOCAL, &sDefault.auth_users,        NULL,0},
 {"charset",           P_STRING, P_LOCAL, &sDefault.charset,           NULL,0},
 {"comment",           P_STRING, P_LOCAL, &sDefault.comment,           NULL,0},
 {"dont compress",     P_STRING, P_LOCAL, &sDefault.dont_compress,     NULL,0},
 {"exclude from",      P_STRING, P_LOCAL, &sDefault.exclude_from,      NULL,0},
 {"exclude",           P_STRING, P_LOCAL, &sDefault.exclude,           NULL,0},
 {"fake super",        P_BOOL,   P_LOCAL, &sDefault.fake_super,        NULL,0},
 {"filter",            P_STRING, P_LOCAL, &sDefault.filter,            NULL,0},
 {"gid",               P_STRING, P_LOCAL, &sDefault.gid,               NULL,0},
 {"hosts allow",       P_STRING, P_LOCAL, &sDefault.hosts_allow,       NULL,0},
 {"hosts deny",        P_STRING, P_LOCAL, &sDefault.hosts_deny,        NULL,0},
 {"ignore errors",     P_BOOL,   P_LOCAL, &sDefault.ignore_errors,     NULL,0},
 {"ignore nonreadable",P_BOOL,   P_LOCAL, &sDefault.ignore_nonreadable,NULL,0},
 {"include from",      P_STRING, P_LOCAL, &sDefault.include_from,      NULL,0},
 {"include",           P_STRING, P_LOCAL, &sDefault.include,           NULL,0},
 {"incoming chmod",    P_STRING, P_LOCAL, &sDefault.incoming_chmod,    NULL,0},
 {"list",              P_BOOL,   P_LOCAL, &sDefault.list,              NULL,0},
 {"lock file",         P_STRING, P_LOCAL, &sDefault.lock_file,         NULL,0},
 {"log file",          P_STRING, P_LOCAL, &sDefault.log_file,          NULL,0},
 {"log format",        P_STRING, P_LOCAL, &sDefault.log_format,        NULL,0},
 {"max connections",   P_INTEGER,P_LOCAL, &sDefault.max_connections,   NULL,0},
 {"max verbosity",     P_INTEGER,P_LOCAL, &sDefault.max_verbosity,     NULL,0},
 {"munge symlinks",    P_BOOL,   P_LOCAL, &sDefault.munge_symlinks,    NULL,0},
 {"name",              P_STRING, P_LOCAL, &sDefault.name,              NULL,0},
 {"numeric ids",       P_BOOL,   P_LOCAL, &sDefault.numeric_ids,       NULL,0},
 {"outgoing chmod",    P_STRING, P_LOCAL, &sDefault.outgoing_chmod,    NULL,0},
 {"path",              P_PATH,   P_LOCAL, &sDefault.path,              NULL,0},
#ifdef HAVE_PUTENV
 {"post-xfer exec",    P_STRING, P_LOCAL, &sDefault.postxfer_exec,     NULL,0},
 {"pre-xfer exec",     P_STRING, P_LOCAL, &sDefault.prexfer_exec,      NULL,0},
#endif
 {"read only",         P_BOOL,   P_LOCAL, &sDefault.read_only,         NULL,0},
 {"refuse options",    P_STRING, P_LOCAL, &sDefault.refuse_options,    NULL,0},
 {"secrets file",      P_STRING, P_LOCAL, &sDefault.secrets_file,      NULL,0},
 {"strict modes",      P_BOOL,   P_LOCAL, &sDefault.strict_modes,      NULL,0},
 {"syslog facility",   P_ENUM,   P_LOCAL, &sDefault.syslog_facility,enum_facilities,0},
 {"temp dir",          P_PATH,   P_LOCAL, &sDefault.temp_dir,          NULL,0},
 {"timeout",           P_INTEGER,P_LOCAL, &sDefault.timeout,           NULL,0},
 {"transfer logging",  P_BOOL,   P_LOCAL, &sDefault.transfer_logging,  NULL,0},
 {"uid",               P_STRING, P_LOCAL, &sDefault.uid,               NULL,0},
 {"use chroot",        P_BOOL,   P_LOCAL, &sDefault.use_chroot,        NULL,0},
 {"write only",        P_BOOL,   P_LOCAL, &sDefault.write_only,        NULL,0},
 {NULL,                P_BOOL,   P_NONE,  NULL,                        NULL,0}
};


/***************************************************************************
* Initialise the global parameter structure.
***************************************************************************/
static void init_globals(void)
{
	memset(&Globals, 0, sizeof Globals);
}

/***************************************************************************
* Initialise the sDefault parameter structure.
***************************************************************************/
static void init_locals(void)
{
}


/*
   In this section all the functions that are used to access the
   parameters from the rest of the program are defined
*/

#define FN_GLOBAL_STRING(fn_name,ptr) \
 char *fn_name(void) {return(*(char **)(ptr) ? *(char **)(ptr) : "");}
#define FN_GLOBAL_BOOL(fn_name,ptr) \
 BOOL fn_name(void) {return(*(BOOL *)(ptr));}
#define FN_GLOBAL_CHAR(fn_name,ptr) \
 char fn_name(void) {return(*(char *)(ptr));}
#define FN_GLOBAL_INTEGER(fn_name,ptr) \
 int fn_name(void) {return(*(int *)(ptr));}

#define FN_LOCAL_STRING(fn_name,val) \
 char *fn_name(int i) {return((LP_SNUM_OK(i)&&pSERVICE(i)->val)?pSERVICE(i)->val : (sDefault.val?sDefault.val:""));}
#define FN_LOCAL_BOOL(fn_name,val) \
 BOOL fn_name(int i) {return(LP_SNUM_OK(i)? pSERVICE(i)->val : sDefault.val);}
#define FN_LOCAL_CHAR(fn_name,val) \
 char fn_name(int i) {return(LP_SNUM_OK(i)? pSERVICE(i)->val : sDefault.val);}
#define FN_LOCAL_INTEGER(fn_name,val) \
 int fn_name(int i) {return(LP_SNUM_OK(i)? pSERVICE(i)->val : sDefault.val);}


FN_GLOBAL_STRING(lp_bind_address, &Globals.bind_address)
FN_GLOBAL_STRING(lp_motd_file, &Globals.motd_file)
FN_GLOBAL_STRING(lp_pid_file, &Globals.pid_file)
FN_GLOBAL_STRING(lp_socket_options, &Globals.socket_options)

FN_GLOBAL_INTEGER(lp_rsync_port, &Globals.rsync_port)

FN_LOCAL_STRING(lp_auth_users, auth_users)
FN_LOCAL_STRING(lp_charset, charset)
FN_LOCAL_STRING(lp_comment, comment)
FN_LOCAL_STRING(lp_dont_compress, dont_compress)
FN_LOCAL_STRING(lp_exclude, exclude)
