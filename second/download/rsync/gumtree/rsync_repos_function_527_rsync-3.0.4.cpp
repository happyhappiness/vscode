static void read_final_goodbye(int f_in)
{
	int i, iflags, xlen;
	uchar fnamecmp_type;
	char xname[MAXPATHLEN];

	if (protocol_version < 29)
		i = read_int(f_in);
	else {
		i = read_ndx_and_attrs(f_in, &iflags, &fnamecmp_type,
				       xname, &xlen);
	}

	if (i != NDX_DONE) {
		rprintf(FERROR, "Invalid packet at end of run (%d) [%s]\n",
			i, who_am_i());
		exit_cleanup(RERR_PROTOCOL);
	}
}