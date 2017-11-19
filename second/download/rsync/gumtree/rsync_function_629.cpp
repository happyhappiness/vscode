int copy_file(char *source, char *dest, mode_t mode)
{
	int ifd;
	int ofd;
	char buf[1024 * 8];
	int len;   /* Number of bytes read into `buf'. */

	ifd = open(source, O_RDONLY);
	if (ifd == -1) {
		fprintf(FERROR,"open %s: %s\n",
			source,strerror(errno));
		return -1;
	}

	if (do_unlink(dest) && errno != ENOENT) {
		fprintf(FERROR,"unlink %s: %s\n",
			dest,strerror(errno));
		return -1;
	}

	ofd = do_open(dest, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, mode);
	if (ofd < 0) {
		fprintf(FERROR,"open %s: %s\n",
			dest,strerror(errno));
		close(ifd);
		return -1;
	}

	while ((len = safe_read(ifd, buf, sizeof(buf))) > 0) {
		if (full_write(ofd, buf, len) < 0) {
			fprintf(FERROR,"write %s: %s\n",
				dest,strerror(errno));
			close(ifd);
			close(ofd);
			return -1;
		}
	}

	close(ifd);
	close(ofd);

	if (len < 0) {
		fprintf(FERROR,"read %s: %s\n",
			source,strerror(errno));
		return -1;
	}

	return 0;
}