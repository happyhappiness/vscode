    }



    if (szFilePart < buf+3) {

	ap_assert(strlen(buf) < nCanon);

        strcpy(szCanon, buf);

	if(szCanon[0] != '\\') { /* a \ at the start means it is UNC, otherwise it is x: */

	    ap_assert(isalpha(szCanon[0]));

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

        return;

    }

    if (szFilePart != buf+3) {

        char b2[_MAX_PATH];

        ap_assert(szFilePart > buf+3);



        szFilePart[-1]='\0';

        sub_canonical_filename(b2, sizeof b2, buf);



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

	ap_assert(strlen(szCanon)+strlen(szFilePart) < nCanon);

        strcat(szCanon, szFilePart);

    }

    else {

	ap_assert(strlen(szCanon)+strlen(d.cFileName) < nCanon);

        strlwr(d.cFileName);

        strcat(szCanon, d.cFileName);

    }

}



/* UNC requires backslashes, hence the conversion before canonicalisation. Not sure how

 * many backslashes (could be that \\machine\share\some/path/is/ok for example). For now, do

 * them all.

 */

API_EXPORT(char *) ap_os_canonical_filename(pool *pPool, const char *szFile)

{

    char buf[HUGE_STRING_LEN];

    char b2[HUGE_STRING_LEN];

    char *s;



    ap_assert(strlen(szFile) < sizeof b2);

    strcpy(b2,szFile);

    for(s=b2 ; *s ; ++s)

	if(*s == '/')

	    *s='\\';



    sub_canonical_filename(buf, sizeof buf, b2);

    buf[0]=tolower(buf[0]);



    if (*szFile && szFile[strlen(szFile)-1] == '/' && buf[strlen(buf)-1] != '/') {

	ap_assert(strlen(buf)+1 < sizeof buf);

        strcat(buf, "/");

    }



    return ap_pstrdup(pPool, buf);

}



/* Win95 doesn't like trailing /s. NT and Unix don't mind. This works 

 * around the problem.

 * Errr... except if it is UNC and we are referring to the root of the UNC, we MUST have

 * a trailing \ and we can't use /s. Jeez. Not sure if this refers to all UNCs or just roots,

 * but I'm going to fix it for all cases for now. (Ben)

 */



#undef stat

API_EXPORT(int) os_stat(const char *szPath, struct stat *pStat)

{

    int n;



    ap_assert(szPath[1] == ':' || szPath[1] == '/');	// we are dealing with either UNC or a drive



    if(szPath[0] == '/') {

	char buf[_MAX_PATH];

	char *s;

	int nSlashes=0;



