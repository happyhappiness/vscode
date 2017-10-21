		
		if (!*fname)
			fname = ".";
		
		if (dir && *dir) {
			if (getcwd(dbuf,MAXPATHLEN-1) == NULL) {
				rprintf(FERROR,"getwd : %s\n",strerror(errno));
				exit_cleanup(1);
			}
			if (chdir(dir) != 0) {
				io_error=1;
				rprintf(FERROR,"chdir %s : %s\n",
					dir,strerror(errno));
				continue;
			}
			flist_dir = dir;
			if (one_file_system)
				set_filesystem(fname);
			send_file_name(f,flist,fname,recurse,FLAG_DELETE);
			flist_dir = NULL;
			if (chdir(dbuf) != 0) {
				rprintf(FERROR,"chdir %s : %s\n",
					dbuf,strerror(errno));
				exit_cleanup(1);
			}
			continue;
		}
		
