{
	const unsigned char *p;
	int extdsize, namelen;
	unsigned char headersum, sum_calculated;

	if ((p = __archive_read_ahead(a, H0_FIXED_SIZE, NULL)) == NULL)
		return (truncated_error(a));
	lha->header_size = p[H0_HEADER_SIZE_OFFSET] + 2;
	headersum = p[H0_HEADER_SUM_OFFSET];
	lha->compsize = archive_le32dec(p + H0_COMP_SIZE_OFFSET);
	lha->origsize = archive_le32dec(p + H0_ORIG_SIZE_OFFSET);
	lha->mtime = lha_dos_time(p + H0_DOS_TIME_OFFSET);
	namelen = p[H0_NAME_LEN_OFFSET];
	extdsize = (int)lha->header_size - H0_FIXED_SIZE - namelen;
	if ((namelen > 221 || extdsize < 0) && extdsize != -2) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Invalid LHa header");
		return (ARCHIVE_FATAL);
	}
	if ((p = __archive_read_ahead(a, lha->header_size, NULL)) == NULL)
		return (truncated_error(a));

	archive_strncpy(&lha->filename, p + H0_FILE_NAME_OFFSET, namelen);
	/* When extdsize == -2, A CRC16 value is not present in the header. */
	if (extdsize >= 0) {
		lha->crc = archive_le16dec(p + H0_FILE_NAME_OFFSET + namelen);
		lha->setflag |= CRC_IS_SET;
	}
	sum_calculated = lha_calcsum(0, p, 2, lha->header_size - 2);

	/* Read an extended header */
	if (extdsize > 0) {
		/* This extended data is set by 'LHa for UNIX' only.
		 * Maybe fixed size.
		 */
		p += H0_FILE_NAME_OFFSET + namelen + 2;
		if (p[0] == 'U' && extdsize == 12) {
			/* p[1] is a minor version. */
			lha->mtime = archive_le32dec(&p[2]);
			lha->mode = archive_le16dec(&p[6]);
			lha->uid = archive_le16dec(&p[8]);
			lha->gid = archive_le16dec(&p[10]);
			lha->setflag |= UNIX_MODE_IS_SET;
		}
	}
	__archive_read_consume(a, lha->header_size);

	if (sum_calculated != headersum) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "LHa header sum error");
		return (ARCHIVE_FATAL);
	}

	return (ARCHIVE_OK);
}