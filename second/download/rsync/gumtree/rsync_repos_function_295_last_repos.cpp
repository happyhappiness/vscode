static int read_delay_line(char *buf, int *flags_p)
{
	static int read_pos = 0;
	int j, len, mode;
	char *bp, *past_space;

	while (1) {
		for (j = read_pos; j < deldelay_cnt && deldelay_buf[j]; j++) {}
		if (j < deldelay_cnt)
			break;
		if (deldelay_fd < 0) {
			if (j > read_pos)
				goto invalid_data;
			return -1;
		}
		deldelay_cnt -= read_pos;
		if (deldelay_cnt == deldelay_size)
			goto invalid_data;
		if (deldelay_cnt && read_pos) {
			memmove(deldelay_buf, deldelay_buf + read_pos,
				deldelay_cnt);
		}
		len = read(deldelay_fd, deldelay_buf + deldelay_cnt,
			   deldelay_size - deldelay_cnt);
		if (len == 0) {
			if (deldelay_cnt) {
				rprintf(FERROR,
				    "ERROR: unexpected EOF in delete-delay file.\n");
			}
			return -1;
		}
		if (len < 0) {
			rsyserr(FERROR, errno,
				"reading delete-delay file");
			return -1;
		}
		deldelay_cnt += len;
		read_pos = 0;
	}

	bp = deldelay_buf + read_pos;
	if (*bp == '!') {
		bp++;
		*flags_p = DEL_NO_UID_WRITE;
	} else
		*flags_p = 0;

	if (sscanf(bp, "%x ", &mode) != 1) {
	  invalid_data:
		rprintf(FERROR, "ERROR: invalid data in delete-delay file.\n");
		return -1;
	}
	past_space = strchr(bp, ' ') + 1;
	len = j - read_pos - (past_space - bp) + 1; /* count the '\0' */
	read_pos = j + 1;

	if (len > MAXPATHLEN) {
		rprintf(FERROR, "ERROR: filename too long in delete-delay file.\n");
		return -1;
	}

	/* The caller needs the name in a MAXPATHLEN buffer, so we copy it
	 * instead of returning a pointer to our buffer. */
	memcpy(buf, past_space, len);

	return mode;
}