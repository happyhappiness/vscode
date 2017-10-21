rprintf(FERROR,"(%d) Error reading %d bytes : %s\n",
					getpid(),8,ret==-1?strerror(errno):"EOF");