int64 read_longint(int f)
{
	extern int remote_version;
	int64 ret;
	char b[8];
	ret = read_int(f);

	if ((int32)ret != (int32)0xffffffff) {
		return ret;
	}

#ifdef NO_INT64
	rprintf(FERROR,"Integer overflow - attempted 64 bit offset\n");
	exit_cleanup(RERR_UNSUPPORTED);
#else
	if (remote_version >= 16) {
		readfd(f,b,8);
		ret = IVAL(b,0) | (((int64)IVAL(b,4))<<32);
	}
#endif

	return ret;
}