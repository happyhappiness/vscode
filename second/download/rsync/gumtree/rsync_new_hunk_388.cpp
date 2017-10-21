					dir,strerror(errno));
				continue;
			}
			flist_dir = dir;
			if (one_file_system)
				set_filesystem(fname);
			send_file_name(f,flist,fname,recurse,FLAG_DELETE);
			flist_dir = NULL;
			if (chdir(dbuf) != 0) {
				fprintf(FERROR,"chdir %s : %s\n",
					dbuf,strerror(errno));
				exit_cleanup(1);
			}
			continue;
		}
		
		if (one_file_system)
			set_filesystem(fname);
		send_file_name(f,flist,fname,recurse,FLAG_DELETE);
	}

	if (f != -1) {
		send_file_entry(NULL,f,0);
		write_flush(f);
	}

	if (verbose && recurse && !am_server && f != -1)
		fprintf(FINFO,"done\n");
	
