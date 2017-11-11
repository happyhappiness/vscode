static void handle_delayed_updates(struct file_list *flist, char *local_name)
{
	char *fname, *partialptr, numbuf[4];
	int i;

	for (i = -1; (i = next_delayed_bit(i)) >= 0; ) {
		struct file_struct *file = flist->files[i];
		fname = local_name ? local_name : f_name(file);
		if ((partialptr = partial_dir_fname(fname)) != NULL) {
			if (make_backups && !make_backup(fname))
				continue;
			if (verbose > 2) {
				rprintf(FINFO, "renaming %s to %s\n",
					safe_fname(partialptr),
					safe_fname(fname));
			}
			if (do_rename(partialptr, fname) < 0) {
				rsyserr(FERROR, errno,
					"rename failed for %s (from %s)",
					full_fname(fname),
					safe_fname(partialptr));
			} else {
				if (remove_sent_files
				    || (preserve_hard_links
				     && file->link_u.links)) {
					SIVAL(numbuf, 0, i);
					send_msg(MSG_SUCCESS,numbuf,4);
				}
				handle_partial_dir(partialptr,
						   PDIR_DELETE);
			}
		}
	}
}