		argstr[x++] = 'x';
	if (sparse_files)
		argstr[x++] = 'S';
	if (do_compression)
		argstr[x++] = 'z';

	/* this is a complete hack - blame Rusty 

	   this is a hack to make the list_only (remote file list)
	   more useful */
	if (list_only && !recurse) 
		argstr[x++] = 'r';

	argstr[x] = 0;

	if (x != 1) args[ac++] = argstr;

	if (block_size != BLOCK_SIZE) {
		snprintf(bsize,sizeof(bsize),"-B%d",block_size);
		args[ac++] = bsize;
	}    

	if (max_delete && am_sender) {
		snprintf(mdelete,sizeof(mdelete),"--max-delete=%d",max_delete);
		args[ac++] = mdelete;
	}    
	
	if (batch_prefix != NULL) {
		char *fmt = "";
		if (write_batch)
		    fmt = "--write-batch=%s";
		else
		if (read_batch)
		    fmt = "--read-batch=%s";
		snprintf(fext,sizeof(fext),fmt,batch_prefix);
		args[ac++] = fext;
	}

	if (io_timeout) {
		snprintf(iotime,sizeof(iotime),"--timeout=%d",io_timeout);
		args[ac++] = iotime;
	}    

	if (bwlimit) {
		snprintf(bw,sizeof(bw),"--bwlimit=%d",bwlimit);
		args[ac++] = bw;
	}

	if (strcmp(backup_suffix, BACKUP_SUFFIX)) {
		args[ac++] = "--suffix";
		args[ac++] = backup_suffix;
	}

	if (delete_mode && !delete_excluded)
		args[ac++] = "--delete";

	if (delete_excluded)
