	    mb = ap_cpystrn(mb, linebuff+4, me - mb);

	} while (memcmp(linebuff, buff, 4) != 0);

    }

    return status;

}



static long int send_dir(BUFF *f, request_rec *r, BUFF *f2, struct cache_req *c, char *url)

{

    char buf[IOBUFSIZE];

    char buf2[IOBUFSIZE];

    char *filename;

    char *tempurl;

    int searchidx = 0;

    char *searchptr = NULL;

    int firstfile = 1;

    char urlptr[HUGE_STRING_LEN];

    unsigned long total_bytes_sent = 0;

    register int n, o, w;

    int hostlen;

    conn_rec *con = r->connection;

    char *dir, *path, *reldir, *site, *psite;

    const char *sig;



    tempurl = ap_pstrdup(r->pool, url);



    (void)decodeenc(tempurl);



    /* Determine length of "scheme://site" prefix */

    for (hostlen=0; tempurl[hostlen]!='/'; ++hostlen)

	continue;

    if (tempurl[hostlen] == '/' && tempurl[hostlen+1] == '/') {

	for (hostlen+=2; tempurl[hostlen]!='/' && tempurl[hostlen]!='?'; ++hostlen)

	    continue;

    } else {

	hostlen = 0;

    }



    /* Save "scheme://site" prefix */

    site = psite = ap_pstrndup(r->pool, tempurl, hostlen);



    if ((n = strcspn(tempurl, "@")) != strlen(tempurl) && n < hostlen) {    /* hide user/passwd */

	memmove(tempurl + (n - 5), tempurl, 6);

	tempurl += n - 5;	/* leave room for ftp:// */

	hostlen -= (n-5);



	/* Save "scheme://site" prefix without user/password */

	site = ap_pstrndup(r->pool, tempurl, hostlen);

    }



    /* Copy path, strip (all except the last) trailing slashes */

    path = dir = ap_pstrcat(r->pool, tempurl+hostlen, "/", NULL);

    while ((n = strlen(path)) > 1 && path[n-1] == '/' && path[n-2] == '/')

	path[n-1] = '\0';



    /* print "ftp://host/" */

    ap_snprintf(buf, sizeof(buf), "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\">\n"

		"<HTML><HEAD><TITLE>%s</TITLE>\n"

		"<BASE HREF=\"%s%s\"></HEAD>\n"

		"<BODY><H2>Directory of "

		"<A HREF=\"/\">%s</A>/",

		tempurl, psite, path, site);

    ap_bputs(buf, con->client);

    if (f2 != NULL)

	ap_bputs(buf, f2);

    total_bytes_sent += strlen(buf);



    while ((dir = strchr(dir+1, '/')) != NULL)

    {

	*dir = '\0';

	if ((reldir = strrchr(path+1, '/'))==NULL)

	    reldir = path+1;

	else

	    ++reldir;

	/* print "path/" component */

	ap_snprintf(buf, sizeof(buf), "<A HREF=\"/%s/\">%s</A>/", path+1, reldir);

	ap_bputs(buf, con->client);

    if (f2 != NULL)

	    ap_bputs(buf, f2);

	total_bytes_sent += strlen(buf);

	*dir = '/';

    }

    ap_snprintf(buf, sizeof(buf), "</H2>\n<HR><PRE>");

    ap_bputs(buf, con->client);

    if (f2 != NULL)

	    ap_bputs(buf, f2);

    total_bytes_sent += strlen(buf);



    for (hostlen=0; url[hostlen]!='/'; ++hostlen)

	continue;

    if (url[hostlen] == '/' && url[hostlen+1] == '/') {

	for (hostlen+=2; url[hostlen]!='/' && url[hostlen]!='?'; ++hostlen)

	    continue;

    } else

	hostlen = 0;



    while (!con->aborted) {

	n = ap_bgets(buf, sizeof buf, f);

	if (n == -1) {		/* input error */

	    if (f2 != NULL)

		f2 = ap_proxy_cache_error(c);

	    break;

	}

	if (n == 0)

	    break;		/* EOF */

	if (buf[0] == 'l' && (filename=strstr(buf, " -> ")) != NULL) {

	    char *link_ptr = filename;



	    do

		filename--;

	    while (filename[0] != ' ');

	    *(filename++) = 0;

	    *(link_ptr++) = 0;

	    if ((n = strlen(link_ptr)) > 1 && link_ptr[n - 1] == '\n')

	      link_ptr[n - 1] = '\0';

	    ap_snprintf(urlptr, sizeof(urlptr), "%s%s%s", url+hostlen, (url[strlen(url) - 1] == '/' ? "" : "/"), filename);

	    ap_snprintf(buf2, sizeof(buf2), "%s <A HREF=\"%s\">%s %s</A>\n", buf, filename, filename, link_ptr);

	    ap_cpystrn(buf, buf2, sizeof(buf));

	    n = strlen(buf);

	}

	else if (buf[0] == 'd' || buf[0] == '-' || buf[0] == 'l' || ap_isdigit(buf[0])) {

	    if (ap_isdigit(buf[0])) {	/* handle DOS dir */

