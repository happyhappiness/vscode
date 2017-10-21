	if (f != -1) {
		send_file_entry(NULL,f,0);
		write_flush(f);
	}

	if (verbose && recurse && !am_server && f != -1)
		rprintf(FINFO,"done\n");
	
	clean_flist(flist);
	
	/* now send the uid/gid list. This was introduced in protocol
           version 15 */
	if (f != -1 && remote_version >= 15) {
