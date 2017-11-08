static void delete_one(struct file_struct *f)
{
	if (!S_ISDIR(f->mode)) {
		if (robust_unlink(f_name(f)) != 0) {
			rprintf(FERROR,"delete_one: unlink %s: %s\n",f_name(f),strerror(errno));
		} else if (verbose) {
			rprintf(FINFO,"deleting %s\n",f_name(f));
		}
	} else {    
		if (do_rmdir(f_name(f)) != 0) {
			if (errno != ENOTEMPTY && errno != EEXIST)
				rprintf(FERROR,"delete_one: rmdir %s: %s\n",
                                        f_name(f), strerror(errno));
		} else if (verbose) {
			rprintf(FINFO,"deleting directory %s\n",f_name(f));      
		}
	}
}