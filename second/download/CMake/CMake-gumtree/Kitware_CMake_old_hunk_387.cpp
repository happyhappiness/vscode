			archive_set_error(&a->archive, errno, "fchdir failed");
			return (ARCHIVE_FAILED);
		}
		vr = statvfs(".", &svfs);
		r = statfs(".", &sfs);
		if (r == 0)
			xr = get_xfer_size(t, -1, ".");
