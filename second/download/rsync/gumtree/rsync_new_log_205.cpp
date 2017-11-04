fprintf(FERROR,"(%d) Error reading %d bytes : %s\n",
	      getpid(),4,ret==-1?strerror(errno):"EOF");