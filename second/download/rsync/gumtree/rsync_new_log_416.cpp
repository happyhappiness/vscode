rprintf(FERROR,"write_buf failed : %s\n",
	    ret==-1?strerror(errno):"EOF");