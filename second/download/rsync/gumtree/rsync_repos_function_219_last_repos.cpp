void check_batch_flags(void)
{
	int i;

	if (protocol_version < 29)
		flag_ptr[7] = NULL;
	else if (protocol_version < 30)
		flag_ptr[9] = NULL;
	tweaked_append = append_mode == 1;
	tweaked_append_verify = append_mode == 2;
#ifdef ICONV_OPTION
	tweaked_iconv = iconv_opt != NULL;
#endif
	for (i = 0; flag_ptr[i]; i++) {
		int set = batch_stream_flags & (1 << i) ? 1 : 0;
		if (*flag_ptr[i] != set) {
			if (i == 9) {
				rprintf(FERROR,
					"%s specify the --iconv option to use this batch file.\n",
					set ? "Please" : "Do not");
				exit_cleanup(RERR_SYNTAX);
			}
			if (INFO_GTE(MISC, 1)) {
				rprintf(FINFO,
					"%sing the %s option to match the batchfile.\n",
					set ? "Sett" : "Clear", flag_name[i]);
			}
			*flag_ptr[i] = set;
		}
	}
	if (protocol_version < 29) {
		if (recurse)
			xfer_dirs |= 1;
		else if (xfer_dirs < 2)
			xfer_dirs = 0;
	}

	if (tweaked_append)
		append_mode = 1;
	else if (tweaked_append_verify)
		append_mode = 2;
}