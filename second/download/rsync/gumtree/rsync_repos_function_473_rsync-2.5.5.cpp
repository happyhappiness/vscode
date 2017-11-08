int poptReadConfigFile(poptContext con, const char * fn) {
    char * file=NULL, * chptr, * end;
    char * buf=NULL, * dst;
    int fd, rc;
    int fileLength;

    fd = open(fn, O_RDONLY);
    if (fd < 0) {
	if (errno == ENOENT)
	    return 0;
	else 
	    return POPT_ERROR_ERRNO;
    }

    fileLength = lseek(fd, 0, SEEK_END);
    (void) lseek(fd, 0, 0);

    file = malloc(fileLength + 1);
    if (read(fd, file, fileLength) != fileLength) {
	rc = errno;
	close(fd);
	errno = rc;
	if (file) free(file);
	return POPT_ERROR_ERRNO;
    }
    close(fd);

    dst = buf = malloc(fileLength + 1);

    chptr = file;
    end = (file + fileLength);
    while (chptr < end) {
	switch (*chptr) {
	  case '\n':
	    *dst = '\0';
	    dst = buf;
	    while (*dst && isspace(*dst)) dst++;
	    if (*dst && *dst != '#') {
		configLine(con, dst);
	    }
	    chptr++;
	    break;
	  case '\\':
	    *dst++ = *chptr++;
	    if (chptr < end) {
		if (*chptr == '\n') 
		    dst--, chptr++;	
		    /* \ at the end of a line does not insert a \n */
		else
		    *dst++ = *chptr++;
	    }
	    break;
	  default:
	    *dst++ = *chptr++;
	    break;
	}
    }

    free(file);
    free(buf);

    return 0;
}