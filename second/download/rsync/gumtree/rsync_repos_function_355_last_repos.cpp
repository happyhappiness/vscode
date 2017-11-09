int hard_link_one(struct file_struct *file, const char *fname,
		  const char *oldname, int terse)
{
	if (do_link(oldname, fname) < 0) {
		enum logcode code;
		if (terse) {
			if (!INFO_GTE(NAME, 1))
				return 0;
			code = FINFO;
		} else
			code = FERROR_XFER;
		rsyserr(code, errno, "link %s => %s failed",
			full_fname(fname), oldname);
		return 0;
	}

	file->flags |= FLAG_HLINK_DONE;

	return 1;
}