fprintf(FERROR,"Error reading %d bytes : %s\n",
	      len,ret==-1?strerror(errno):"EOF");