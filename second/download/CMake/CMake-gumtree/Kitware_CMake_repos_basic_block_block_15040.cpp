{
		int dffd, tmpfd;

		tmpfd = create_tempdatafork(a, metadata);
		if (tmpfd == -1)
			return (ARCHIVE_WARN);

		/*
		 * Do not open the data fork compressed by HFS+ compression
		 * with at least a writing mode(O_RDWR or O_WRONLY). it
		 * makes the data fork uncompressed.
		 */
		dffd = open(datafork, 0);
		if (dffd == -1) {
			archive_set_error(&a->archive, errno,
			    "Failed to open the data fork for metadata");
			close(tmpfd);
			return (ARCHIVE_WARN);
		}

#if defined(HAVE_SYS_XATTR_H)
		ret = copy_xattrs(a, tmpfd, dffd);
		if (ret == ARCHIVE_OK)
#endif
			ret = copy_acls(a, tmpfd, dffd);
		close(tmpfd);
		close(dffd);
	}