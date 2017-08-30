			archive_set_error(&a->archive, errno, "fchdir failed");

			return (ARCHIVE_FAILED);

		}

#if defined(HAVE_STATVFS)

		vr = statvfs(".", &svfs);

#endif

		r = statfs(".", &sfs);

		if (r == 0)

			xr = get_xfer_size(t, -1, ".");

