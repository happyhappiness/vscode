void write_longint(int f, int64 x)
{
	extern int remote_version;
	char b[8];
	int ret;

	if (remote_version < 16 || x <= 0x7FFFFFFF) {
		write_int(f, (int)x);
		return;
	}

	write_int(f, -1);
	SIVAL(b,0,(x&0xFFFFFFFF));
	SIVAL(b,4,((x>>32)&0xFFFFFFFF));

	if ((ret=writefd(f,b,8)) != 8) {
		fprintf(FERROR,"write_longint failed : %s\n",
			ret==-1?strerror(errno):"EOF");
		exit_cleanup(1);
	}
	total_written += 8;
}