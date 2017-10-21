{
	extern int remote_version;
	int64 ret;
	char b[8];
	ret = read_int(f);

	if ((int32)ret != (int32)0xffffffff) return ret;

#ifdef NO_INT64
	rprintf(FERROR,"Integer overflow - attempted 64 bit offset\n");
	exit_cleanup(1);
#else
	if (remote_version >= 16) {
		if ((ret=readfd(f,b,8)) != 8) {
			if (verbose > 1) 
				rprintf(FERROR,"(%d) Error reading %d bytes : %s\n",
					getpid(),8,ret==-1?strerror(errno):"EOF");
			exit_cleanup(1);
		}
		total_read += 8;
		ret = IVAL(b,0) | (((int64)IVAL(b,4))<<32);
	}
