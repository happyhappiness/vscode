{

    request_rec *r = ((include_cmd_arg *) arg)->r;

    char *s = ((include_cmd_arg *) arg)->s;

    table *env = r->subprocess_env;

    int child_pid = 0;

#ifdef DEBUG_INCLUDE_CMD

    FILE *dbg = fopen("/dev/tty", "w");

#endif

#ifndef WIN32

    char err_string[MAX_STRING_LEN];

#endif



#ifdef DEBUG_INCLUDE_CMD

#ifdef __EMX__

    /* under OS/2 /dev/tty is referenced as con */

    FILE *dbg = fopen("con", "w");

#else

    fprintf(dbg, "Attempting to include command '%s'\n", s);

#endif

#endif



    if (r->path_info && r->path_info[0] != '\0') {

        request_rec *pa_req;



        ap_table_setn(env, "PATH_INFO", ap_escape_shell_cmd(r->pool, r->path_info));



