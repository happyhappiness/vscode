
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

	ap_assert(strlen(szPath) < _MAX_PATH);
	strcpy(buf,szPath);
	for(s=buf ; *s ; ++s)
	    if(*s == '/') {
		*s='\\';
		++nSlashes;
	    }
	if(nSlashes == 3)   /* then we need to add one more to get \\machine\share\ */
	    *s++='\\';
	*s='\0';
	return stat(buf,pStat);
    }

    n = strlen(szPath);
    if(szPath[n-1] == '\\' || szPath[n-1] == '/') {
        char buf[_MAX_PATH];
        
        ap_assert(n < _MAX_PATH);
        strcpy(buf, szPath);
        buf[n-1] = '\0';
        
        return stat(buf, pStat);
    }
    return stat(szPath, pStat);
}

