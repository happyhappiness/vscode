rprintf(FERROR,"(%d) Error reading %d bytes : %s\n",
	      getpid(),len,ret==-1?strerror(errno):"EOF");