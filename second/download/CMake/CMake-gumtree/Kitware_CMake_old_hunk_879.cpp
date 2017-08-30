			    "Couldn't read link data");

			return (ARCHIVE_FAILED);

		}

#ifdef HAVE_READLINKAT

		if (a->entry_wd_fd >= 0)

			lnklen = readlinkat(a->entry_wd_fd, path,

			    linkbuffer, linkbuffer_len);

		else

#endif /* HAVE_READLINKAT */

		lnklen = readlink(path, linkbuffer, linkbuffer_len);

		if (lnklen < 0) {

			archive_set_error(&a->archive, errno,

			    "Couldn't read link data");

