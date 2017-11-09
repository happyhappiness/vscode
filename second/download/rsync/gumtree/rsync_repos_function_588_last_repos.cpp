static void read_final_goodbye(int f_in, int f_out)
{
	int i, iflags, xlen;
	uchar fnamecmp_type;
	char xname[MAXPATHLEN];

	shutting_down = True;

	if (protocol_version < 29)
		i = read_int(f_in);
	else {
		i = read_ndx_and_attrs(f_in, f_out, &iflags, &fnamecmp_type, xname, &xlen);
		if (protocol_version >= 31 && i == NDX_DONE) {
			if (am_sender)
				write_ndx(f_out, NDX_DONE);
			else {
				if (batch_gen_fd >= 0) {
					while (read_int(batch_gen_fd) != NDX_DEL_STATS) {}
					read_del_stats(batch_gen_fd);
				}
				write_int(f_out, NDX_DONE);
			}
			i = read_ndx_and_attrs(f_in, f_out, &iflags, &fnamecmp_type, xname, &xlen);
		}
	}

	if (i != NDX_DONE) {
		rprintf(FERROR, "Invalid packet at end of run (%d) [%s]\n",
			i, who_am_i());
		exit_cleanup(RERR_PROTOCOL);
	}
}