int read_item_attrs(int f_in, int f_out, int ndx, uchar *type_ptr,
		    char *buf, int *len_ptr)
{
	int len;
	uchar fnamecmp_type = FNAMECMP_FNAME;
	int iflags = protocol_version >= 29 ? read_shortint(f_in)
		   : ITEM_TRANSFER | ITEM_MISSING_DATA;

	/* Handle the new keep-alive (no-op) packet. */
	if (ndx == the_file_list->count && iflags == ITEM_IS_NEW)
		;
	else if (ndx < 0 || ndx >= the_file_list->count) {
		rprintf(FERROR, "Invalid file index: %d (count=%d) [%s]\n",
			ndx, the_file_list->count, who_am_i());
		exit_cleanup(RERR_PROTOCOL);
	} else if (iflags == ITEM_IS_NEW) {
		rprintf(FERROR, "Invalid itemized flag word: %x [%s]\n",
			iflags, who_am_i());
		exit_cleanup(RERR_PROTOCOL);
	}

	if (iflags & ITEM_BASIS_TYPE_FOLLOWS)
		fnamecmp_type = read_byte(f_in);
	*type_ptr = fnamecmp_type;

	if (iflags & ITEM_XNAME_FOLLOWS) {
		if ((len = read_vstring(f_in, buf, MAXPATHLEN)) < 0)
			exit_cleanup(RERR_PROTOCOL);
	} else {
		*buf = '\0';
		len = -1;
	}
	*len_ptr = len;

	if (iflags & ITEM_TRANSFER) {
		if (!S_ISREG(the_file_list->files[ndx]->mode)) {
			rprintf(FERROR,
				"received request to transfer non-regular file: %d [%s]\n",
				ndx, who_am_i());
			exit_cleanup(RERR_PROTOCOL);
		}
	} else if (f_out >= 0) {
		write_ndx_and_attrs(f_out, ndx, iflags,
				    fnamecmp_type, buf, len);
	}

	return iflags;
}