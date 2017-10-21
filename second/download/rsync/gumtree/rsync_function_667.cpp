struct file_list *send_file_list(int f,int argc,char *argv[])
{
	int i,l;
	STRUCT_STAT st;
	char *p,*dir,*olddir;
	char lastpath[MAXPATHLEN]="";
	struct file_list *flist;
	int64 start_write;

	if (verbose && recurse && !am_server && f != -1) {
		rprintf(FINFO,"building file list ... ");
		rflush(FINFO);
	}

	start_write = stats.total_written;

	flist = (struct file_list *)malloc(sizeof(flist[0]));
	if (!flist) out_of_memory("send_file_list");

	flist->count=0;
	flist->malloced = 1000;
	flist->files = (struct file_struct **)malloc(sizeof(flist->files[0])*
						     flist->malloced);
	if (!flist->files) out_of_memory("send_file_list");

	if (f != -1) {
		io_start_buffering(f);
	}

	for (i=0;i<argc;i++) {
		char *fname = topsrcname;

		strlcpy(fname,argv[i],MAXPATHLEN);

		l = strlen(fname);
		if (l != 1 && fname[l-1] == '/') {
			if ((l == 2) && (fname[0] == '.')) {
				/*  Turn ./ into just . rather than ./.
				    This was put in to avoid a problem with
				      rsync -aR --delete from ./
				    The send_file_name() below of ./ was
				    mysteriously preventing deletes */
				fname[1] = 0;
			} else {
				strlcat(fname,".",MAXPATHLEN);
			}
		}

		if (link_stat(fname,&st) != 0) {
			if (f != -1) {
				io_error=1;
				rprintf(FERROR,"link_stat %s : %s\n",fname,strerror(errno));
			}
			continue;
		}

		if (S_ISDIR(st.st_mode) && !recurse) {
			rprintf(FINFO,"skipping directory %s\n",fname);
			continue;
		}

		dir = NULL;
		olddir = NULL;

		if (!relative_paths) {
			p = strrchr(fname,'/');
			if (p) {
				*p = 0;
				if (p == fname) 
					dir = "/";
				else
					dir = fname;      
				fname = p+1;      
			}
		} else if (f != -1 && (p=strrchr(fname,'/'))) {
			/* this ensures we send the intermediate directories,
			   thus getting their permissions right */
			*p = 0;
			if (strcmp(lastpath,fname)) {
				strlcpy(lastpath, fname, sizeof(lastpath));
				*p = '/';
				for (p=fname+1; (p=strchr(p,'/')); p++) {
					int copy_links_saved = copy_links;
					int recurse_saved = recurse;
					*p = 0;
					copy_links = copy_unsafe_links;
					/* set recurse to 1 to prevent make_file
					   from ignoring directory, but still
					   turn off the recursive parameter to
					   send_file_name */
					recurse = 1;
					send_file_name(f, flist, fname, 0, 0);
					copy_links = copy_links_saved;
					recurse = recurse_saved;
					*p = '/';
				}
			} else {
				*p = '/';
			}
		}
		
		if (!*fname)
			fname = ".";
		
		if (dir && *dir) {
			olddir = push_dir(dir, 1);

			if (!olddir) {
				io_error=1;
				rprintf(FERROR,"push_dir %s : %s\n",
					dir,strerror(errno));
				continue;
			}

			flist_dir = dir;
		}
		
		if (one_file_system)
			set_filesystem(fname);

		send_file_name(f,flist,fname,recurse,FLAG_DELETE);

		if (olddir != NULL) {
			flist_dir = NULL;
			if (pop_dir(olddir) != 0) {
				rprintf(FERROR,"pop_dir %s : %s\n",
					dir,strerror(errno));
				exit_cleanup(RERR_FILESELECT);
			}
		}
	}

	topsrcname[0] = '\0';

	if (f != -1) {
		send_file_entry(NULL,f,0);
	}

	if (verbose && recurse && !am_server && f != -1)
		rprintf(FINFO,"done\n");
	
	clean_flist(flist, 0);
	
	/* now send the uid/gid list. This was introduced in protocol
           version 15 */
	if (f != -1 && remote_version >= 15) {
		send_uid_list(f);
	}

	/* if protocol version is >= 17 then send the io_error flag */
	if (f != -1 && remote_version >= 17) {
		extern int module_id;
		write_int(f, lp_ignore_errors(module_id)? 0 : io_error);
	}

	if (f != -1) {
		io_end_buffering(f);
		stats.flist_size = stats.total_written - start_write;
		stats.num_files = flist->count;
	}

	if (verbose > 2)
		rprintf(FINFO,"send_file_list done\n");

	return flist;
}