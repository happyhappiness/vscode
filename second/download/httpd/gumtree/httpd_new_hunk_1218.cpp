	    mb = ap_cpystrn(mb, linebuff+4, me - mb);

	} while (memcmp(linebuff, buff, 4) != 0);

    }

    return status;

}



static long int send_dir(BUFF *f, request_rec *r, cache_req *c, char *cwd)

{

    char buf[IOBUFSIZE];

    char buf2[IOBUFSIZE];

    char *filename;

    int searchidx = 0;

    char *searchptr = NULL;

    int firstfile = 1;

    unsigned long total_bytes_sent = 0;

    register int n, o, w;

    conn_rec *con = r->connection;

    char *dir, *path, *reldir, *site;



    /* Save "scheme://site" prefix without password */

    site = ap_unparse_uri_components(r->pool, &r->parsed_uri, UNP_OMITPASSWORD|UNP_OMITPATHINFO);

    /* ... and path without query args */

    path = ap_unparse_uri_components(r->pool, &r->parsed_uri, UNP_OMITSITEPART|UNP_OMITQUERY);

    (void)decodeenc(path);



    /* Copy path, strip (all except the last) trailing slashes */

    path = dir = ap_pstrcat(r->pool, path, "/", NULL);

    while ((n = strlen(path)) > 1 && path[n-1] == '/' && path[n-2] == '/')

	path[n-1] = '\0';



    /* print "ftp://host/" */

    n = ap_snprintf(buf, sizeof(buf), "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\">\n"

		"<HTML><HEAD><TITLE>%s%s</TITLE>\n"

		"<BASE HREF=\"%s%s\"></HEAD>\n"

		"<BODY><H2>Directory of "

		"<A HREF=\"/\">%s</A>/",

		site, path, site, path, site);

    total_bytes_sent += ap_proxy_bputs2(buf, con->client, c);



    while ((dir = strchr(dir+1, '/')) != NULL)

    {

	*dir = '\0';

	if ((reldir = strrchr(path+1, '/'))==NULL)

	    reldir = path+1;

	else

	    ++reldir;

	/* print "path/" component */

	ap_snprintf(buf, sizeof(buf), "<A HREF=\"/%s/\">%s</A>/", path+1, reldir);

	total_bytes_sent += ap_proxy_bputs2(buf, con->client, c);

	*dir = '/';

    }

    /* If the caller has determined the current directory, and it differs */

    /* from what the client requested, then show the real name */

    if (cwd == NULL || strncmp (cwd, path, strlen(cwd)) == 0) {

	ap_snprintf(buf, sizeof(buf), "</H2>\n<HR><PRE>");

    } else {

	ap_snprintf(buf, sizeof(buf), "</H2>\n(%s)\n<HR><PRE>", cwd);

    }

    total_bytes_sent += ap_proxy_bputs2(buf, con->client, c);



    while (!con->aborted) {

	n = ap_bgets(buf, sizeof buf, f);

	if (n == -1) {		/* input error */

	    if (c != NULL)

		c = ap_proxy_cache_error(c);

	    break;

	}

	if (n == 0)

	    break;		/* EOF */

	if (buf[0] == 'l' && (filename=strstr(buf, " -> ")) != NULL) {

	    char *link_ptr = filename;



	    do {

		filename--;

	    } while (filename[0] != ' ');

	    *(filename++) = '\0';

	    *(link_ptr++) = '\0';

	    if ((n = strlen(link_ptr)) > 1 && link_ptr[n - 1] == '\n')

	      link_ptr[n - 1] = '\0';

	    ap_snprintf(buf2, sizeof(buf2), "%s <A HREF=\"%s\">%s %s</A>\n", buf, filename, filename, link_ptr);

	    ap_cpystrn(buf, buf2, sizeof(buf));

	    n = strlen(buf);

	}

	else if (buf[0] == 'd' || buf[0] == '-' || buf[0] == 'l' || ap_isdigit(buf[0])) {

	    if (ap_isdigit(buf[0])) {	/* handle DOS dir */

