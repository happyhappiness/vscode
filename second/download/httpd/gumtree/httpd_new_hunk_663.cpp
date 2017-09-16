    }



    if (szFilePart < buf+3) {

	ap_assert(strlen(buf) < nCanon);

        strcpy(szCanon, buf);

	if(szCanon[0] != '\\') { /* a \ at the start means it is UNC, otherwise it is x: */

	    ap_assert(ap_isalpha(szCanon[0]));

	    ap_assert(szCanon[1] == ':');

	    szCanon[2] = '/';

	}

	else {

	    char *s;



	    ap_assert(szCanon[1] == '\\');

	    for(s=szCanon ; *s ; ++s)

		if(*s == '\\')

		    *s='/';

	}

        return TRUE;

    }

    if (szFilePart != buf+3) {

        char b2[_MAX_PATH];

	char b3[_MAX_PATH];

        ap_assert(szFilePart > buf+3);

	/* avoid SEGVs on things like "Directory *" */

	ap_assert(s >= szFile && "this is a known bug");



	memcpy(b3,szFile,s-szFile);

	b3[s-szFile]='\0';



//        szFilePart[-1]='\0';

        sub_canonical_filename(b2, sizeof b2, b3);



	ap_assert(strlen(b2)+1 < nCanon);

        strcpy(szCanon, b2);

        strcat(szCanon, "/");

    }

    else {

	ap_assert(strlen(buf) < nCanon);

        strcpy(szCanon, buf);

        szCanon[2] = '/';

        szCanon[3] = '\0';

    }

    if (h == INVALID_HANDLE_VALUE) {

	ap_assert(strlen(szCanon)+strlen(szFilePart)+nSlashes < nCanon);

	for(n=0 ; n < nSlashes ; ++n)

	    strcat(szCanon, "/");

        strcat(szCanon, szFilePart);

	return FALSE;

    }

    else {

	ap_assert(strlen(szCanon)+strlen(d.cFileName) < nCanon);

        strlwr(d.cFileName);

        strcat(szCanon, d.cFileName);

	return TRUE;

    }

}



/* UNC requires backslashes, hence the conversion before canonicalisation. 

 * Not sure how * many backslashes (could be that 

 * \\machine\share\some/path/is/ok for example). For now, do them all.

 */

API_EXPORT(char *) ap_os_canonical_filename(pool *pPool, const char *szFile)

{

    char buf[HUGE_STRING_LEN];

    char b2[HUGE_STRING_LEN];

    const char *s;

    char *d;

    int nSlashes;



    ap_assert(strlen(szFile) < sizeof b2);



    /* Eliminate directories consisting of three or more dots.

       These act like ".." but are not detected by other machinery.

       Also get rid of trailing .s on any path component, which are ignored by the filesystem.

       Simultaneously, rewrite / to \.

       This is a bit of a kludge - Ben.

    */

    for(s=szFile,d=b2 ; (*d=*s) ; ++d,++s) {

	if(*s == '/')

	    *d='\\';

	if(*s == '.' && (s[1] == '/' || s[1] == '\\' || !s[1])) {

	    while(*d == '.')

		--d;

	    if(*d == '\\')

		--d;

	    }

	}

    // Finally, a trailing slash(es) screws thing, so blow them away

    for(nSlashes=0 ; d > b2 && d[-1] == '\\' ; --d,++nSlashes)

	;

    /* XXXX this breaks '/' and 'c:/' cases */

    *d='\0';



    sub_canonical_filename(buf, sizeof buf, b2);



    buf[0]=ap_tolower(buf[0]);



    ap_assert(strlen(buf)+nSlashes < sizeof buf);

    while(nSlashes--)

        strcat(buf, "/");



    return ap_pstrdup(pPool, buf);

}



/* Win95 doesn't like trailing /s. NT and Unix don't mind. This works 

 * around the problem.

 * Errr... except if it is UNC and we are referring to the root of 

 * the UNC, we MUST have a trailing \ and we can't use /s. Jeez. 

 * Not sure if this refers to all UNCs or just roots,

 * but I'm going to fix it for all cases for now. (Ben)

 */



#undef stat

API_EXPORT(int) os_stat(const char *szPath, struct stat *pStat)

{

    int n;



    /* be sure it is has a drive letter or is a UNC path; everything

     * _must_ be canonicalized before getting to this point.  

     */

    if (szPath[1] != ':' && szPath[1] != '/') {

	ap_log_error(APLOG_MARK, APLOG_ERR, NULL, 

	    "Invalid path in os_stat: \"%s\", should have a drive letter "

	    "or be a UNC path", szPath);

	return (-1);

    }



    if(szPath[0] == '/') {

	char buf[_MAX_PATH];

	char *s;

	int nSlashes=0;



++ apache_1.3.1/src/regex/debug.c	1998-07-09 01:47:26.000000000 +0800

