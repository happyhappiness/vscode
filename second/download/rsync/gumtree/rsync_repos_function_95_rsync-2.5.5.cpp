static int keep_backup(char *fname)
{

	static int initialised;

	char keep_name [MAXPATHLEN];
	STRUCT_STAT st;
	struct file_struct *file;

	int kept=0;
	int ret_code;

	if (!initialised) {
		if (backup_dir[strlen(backup_dir) - 1] == '/')
			backup_dir[strlen(backup_dir) - 1] = 0;
		if (verbose > 0)
			rprintf (FINFO, "backup_dir is %s\n", backup_dir);
		initialised = 1;
	}

	/* return if no file to keep */
#if SUPPORT_LINKS
	if (do_lstat (fname, &st)) return 1;
#else
	if (do_stat (fname, &st)) return 1;
#endif

	file = make_file(-1, fname, NULL, 1);

	/* the file could have disappeared */
	if (!file) return 1;

        /* make a complete pathname for backup file */
        if (strlen(backup_dir) + strlen(fname) > (MAXPATHLEN - 1)) {
                rprintf (FERROR, "keep_backup filename too long\n");
                return 0;
        }

        snprintf(keep_name, sizeof (keep_name), "%s/%s", backup_dir, fname);


#ifdef HAVE_MKNOD
	/* Check to see if this is a device file, or link */
        if(IS_DEVICE(file->mode)) {
                if(am_root && preserve_devices) {
                        make_bak_dir(fname,backup_dir);
                        if(do_mknod(keep_name,file->mode,file->rdev)!=0) {
                                rprintf(FERROR,"mknod %s : %s\n",keep_name,strerror(errno));
                        } else {
                                if(verbose>2)
                                        rprintf(FINFO,"make_backup : DEVICE %s successful.\n",fname);
                        };
                };
		kept=1;
                do_unlink(fname);
        };
#endif

	if(!kept && S_ISDIR(file->mode)) {
		/* make an empty directory */
                make_bak_dir(fname,backup_dir);
                do_mkdir(keep_name,file->mode);
                ret_code=do_rmdir(fname);
                if(verbose>2)
                        rprintf(FINFO,"make_backup : RMDIR %s returns %i\n",fname,ret_code);
		kept=1;
        };

#if SUPPORT_LINKS
        if(!kept && preserve_links && S_ISLNK(file->mode)) {
                extern int safe_symlinks;
                if (safe_symlinks && unsafe_symlink(file->link, keep_name)) {
                        if (verbose) {
                                rprintf(FINFO,"ignoring unsafe symlink %s -> %s\n",
                                        keep_name,file->link);
                        }
			kept=1;
                }
                make_bak_dir(fname,backup_dir);
                if(do_symlink(file->link,keep_name) != 0) {
                        rprintf(FERROR,"link %s -> %s : %s\n",keep_name,file->link,strerror(errno));
                };
                do_unlink(fname);
		kept=1;
        };
#endif
        if(!kept && preserve_hard_links && check_hard_link(file)) {
                if(verbose > 1) rprintf(FINFO,"%s is a hard link\n",f_name(file));
        };

        if(!kept && !S_ISREG(file->mode)) {
                rprintf(FINFO,"make_bak: skipping non-regular file %s\n",fname);
        }

	/* move to keep tree if a file */
	if(!kept) {
		if (!robust_move (fname, keep_name))
			rprintf(FERROR, "keep_backup failed %s -> %s : %s\n",
				fname, keep_name, strerror(errno));
	};
	set_perms (keep_name, file, NULL, 0);
	free_file (file);
	free (file);

	if (verbose > 1)
		rprintf (FINFO, "keep_backup %s -> %s\n", fname, keep_name);
	return 1;
}