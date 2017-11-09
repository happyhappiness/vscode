int poptReadConfigFile(poptContext con, const char * fn)
{
    const char * file, * chptr, * end;
    char * buf;
/*@dependent@*/ char * dst;
    int fd, rc;
    off_t fileLength;

    fd = open(fn, O_RDONLY);
    if (fd < 0)
	return (errno == ENOENT ? 0 : POPT_ERROR_ERRNO);

    fileLength = lseek(fd, 0, SEEK_END);
    if (fileLength == -1 || lseek(fd, 0, 0) == -1) {
	rc = errno;
	(void) close(fd);
	errno = rc;
	return POPT_ERROR_ERRNO;
    }

    file = alloca(fileLength + 1);
    if (read(fd, (char *)file, fileLength) != fileLength) {
	rc = errno;
	(void) close(fd);
	errno = rc;
	return POPT_ERROR_ERRNO;
    }
    if (close(fd) == -1)
	return POPT_ERROR_ERRNO;

/*@-boundswrite@*/
    dst = buf = alloca(fileLength + 1);

    chptr = file;
    end = (file + fileLength);
    /*@-infloops@*/	/* LCL: can't detect chptr++ */
    while (chptr < end) {
	switch (*chptr) {
	  case '\n':
	    *dst = '\0';
	    dst = buf;
	    while (*dst && isSpace(dst)) dst++;
	    if (*dst && *dst != '#')
		configLine(con, dst);
	    chptr++;
	    /*@switchbreak@*/ break;
	  case '\\':
	    *dst++ = *chptr++;
	    if (chptr < end) {
		if (*chptr == '\n') 
		    dst--, chptr++;	
		    /* \ at the end of a line does not insert a \n */
		else
		    *dst++ = *chptr++;
	    }
	    /*@switchbreak@*/ break;
	  default:
	    *dst++ = *chptr++;
	    /*@switchbreak@*/ break;
	}
    }
    /*@=infloops@*/
/*@=boundswrite@*/

    return 0;
}