

static int getsfunc_FILE(char *buf, int len, void *f)

{

    return fgets(buf, len, (FILE *) f) != NULL;

}



API_EXPORT(int) ap_scan_script_header_err(request_rec *r, FILE *f, char *buffer)

{

    return scan_script_header_err_core(r, buffer, getsfunc_FILE, f);

}



static int getsfunc_BUFF(char *w, int len, void *fb)

{

    return ap_bgets(w, len, (BUFF *) fb) > 0;

}



API_EXPORT(int) ap_scan_script_header_err_buff(request_rec *r, BUFF *fb,

					    char *buffer)

{

    return scan_script_header_err_core(r, buffer, getsfunc_BUFF, fb);

}





API_EXPORT(void) ap_send_size(size_t size, request_rec *r)

{

    /* XXX: this -1 thing is a gross hack */

    if (size == (size_t)-1)

	ap_rputs("    -", r);

    else if (!size)

	ap_rputs("   0k", r);

    else if (size < 1024)

	ap_rputs("   1k", r);

    else if (size < 1048576)

	ap_rprintf(r, "%4dk", (size + 512) / 1024);

    else if (size < 103809024)

	ap_rprintf(r, "%4.1fM", size / 1048576.0);

    else

	ap_rprintf(r, "%4dM", (size + 524288) / 1048576);

}



#if defined(__EMX__) || defined(WIN32)

static char **create_argv_cmd(pool *p, char *av0, const char *args, char *path)

{

    register int x, n;

    char **av;

    char *w;



    for (x = 0, n = 2; args[x]; x++)

	if (args[x] == '+')

	    ++n;



    /* Add extra strings to array. */

    n = n + 2;



    av = (char **) ap_palloc(p, (n + 1) * sizeof(char *));

    av[0] = av0;

