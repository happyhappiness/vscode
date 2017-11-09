static void log_formatted(enum logcode code, const char *format, const char *op,
			  struct file_struct *file, const char *fname, int iflags,
			  const char *hlink)
{
	char buf[MAXPATHLEN+1024], buf2[MAXPATHLEN], fmt[32];
	char *p, *s, *c;
	const char *n;
	size_t len, total;
	int64 b;

	*fmt = '%';

	/* We expand % codes one by one in place in buf.  We don't
	 * copy in the terminating null of the inserted strings, but
	 * rather keep going until we reach the null of the format. */
	total = strlcpy(buf, format, sizeof buf);
	if (total > MAXPATHLEN) {
		rprintf(FERROR, "log-format string is WAY too long!\n");
		exit_cleanup(RERR_MESSAGEIO);
	}
	buf[total++] = '\n';
	buf[total] = '\0';

	for (p = buf; (p = strchr(p, '%')) != NULL; ) {
		int humanize = 0;
		s = p++;
		c = fmt + 1;
		while (*p == '\'') {
			humanize++;
			p++;
		}
		if (*p == '-')
			*c++ = *p++;
		while (isDigit(p) && c - fmt < (int)(sizeof fmt) - 8)
			*c++ = *p++;
		while (*p == '\'') {
			humanize++;
			p++;
		}
		if (!*p)
			break;
		*c = '\0';
		n = NULL;

		/* Note for %h and %a: it doesn't matter what fd we pass to
		 * client_{name,addr} because rsync_module will already have
		 * forced the answer to be cached (assuming, of course, for %h
		 * that lp_reverse_lookup(module_id) is true). */
		switch (*p) {
		case 'h':
			if (am_daemon) {
				n = lp_reverse_lookup(module_id)
				  ? client_name(0) : undetermined_hostname;
			}
			break;
		case 'a':
			if (am_daemon)
				n = client_addr(0);
			break;
		case 'l':
			strlcat(fmt, "s", sizeof fmt);
			snprintf(buf2, sizeof buf2, fmt,
				 do_big_num(F_LENGTH(file), humanize, NULL));
			n = buf2;
			break;
		case 'U':
			strlcat(fmt, "u", sizeof fmt);
			snprintf(buf2, sizeof buf2, fmt,
				 uid_ndx ? F_OWNER(file) : 0);
			n = buf2;
			break;
		case 'G':
			if (!gid_ndx || file->flags & FLAG_SKIP_GROUP)
				n = "DEFAULT";
			else {
				strlcat(fmt, "u", sizeof fmt);
				snprintf(buf2, sizeof buf2, fmt,
					 F_GROUP(file));
				n = buf2;
			}
			break;
		case 'p':
			strlcat(fmt, "d", sizeof fmt);
			snprintf(buf2, sizeof buf2, fmt, (int)getpid());
			n = buf2;
			break;
		case 'M':
			n = c = timestring(file->modtime);
			while ((c = strchr(c, ' ')) != NULL)
				*c = '-';
			break;
		case 'B':
			c = buf2 + MAXPATHLEN - PERMSTRING_SIZE - 1;
			permstring(c, file->mode);
			n = c + 1; /* skip the type char */
			break;
		case 'o':
			n = op;
			break;
		case 'f':
			if (fname) {
				c = f_name_buf();
				strlcpy(c, fname, MAXPATHLEN);
			} else
				c = f_name(file, NULL);
			if (am_sender && F_PATHNAME(file)) {
				pathjoin(buf2, sizeof buf2,
					 F_PATHNAME(file), c);
				clean_fname(buf2, 0);
				if (fmt[1]) {
					strlcpy(c, buf2, MAXPATHLEN);
					n = c;
				} else
					n = buf2;
			} else if (am_daemon && *c != '/') {
				pathjoin(buf2, sizeof buf2,
					 curr_dir + module_dirlen, c);
				clean_fname(buf2, 0);
				if (fmt[1]) {
					strlcpy(c, buf2, MAXPATHLEN);
					n = c;
				} else
					n = buf2;
			} else {
				clean_fname(c, 0);
				n = c;
			}
			if (*n == '/')
				n++;
			break;
		case 'n':
			if (fname) {
				c = f_name_buf();
				strlcpy(c, fname, MAXPATHLEN);
			} else
				c = f_name(file, NULL);
			if (S_ISDIR(file->mode))
				strlcat(c, "/", MAXPATHLEN);
			n = c;
			break;
		case 'L':
			if (hlink && *hlink) {
				n = hlink;
				strlcpy(buf2, " => ", sizeof buf2);
			} else if (S_ISLNK(file->mode) && !fname) {
				n = F_SYMLINK(file);
				strlcpy(buf2, " -> ", sizeof buf2);
			} else {
				n = "";
				if (!fmt[1])
					break;
				strlcpy(buf2, "    ", sizeof buf2);
			}
			strlcat(fmt, "s", sizeof fmt);
			snprintf(buf2 + 4, sizeof buf2 - 4, fmt, n);
			n = buf2;
			break;
		case 'm':
			n = lp_name(module_id);
			break;
		case 't':
			n = timestring(time(NULL));
			break;
		case 'P':
			n = full_module_path;
			break;
		case 'u':
			n = auth_user;
			break;
		case 'b':
		case 'c':
			if (!(iflags & ITEM_TRANSFER))
				b = 0;
			else if ((!!am_sender) ^ (*p == 'c'))
				b = total_data_written - initial_data_written;
			else
				b = total_data_read - initial_data_read;
			strlcat(fmt, "s", sizeof fmt);
			snprintf(buf2, sizeof buf2, fmt,
				 do_big_num(b, humanize, NULL));
			n = buf2;
			break;
		case 'C':
			if (protocol_version >= 30
			 && (iflags & ITEM_TRANSFER
			  || (always_checksum && S_ISREG(file->mode)))) {
				const char *sum = iflags & ITEM_TRANSFER
						? sender_file_sum : F_SUM(file);
				n = sum_as_hex(sum);
			} else {
				memset(buf2, ' ', checksum_len*2);
				buf2[checksum_len*2] = '\0';
				n = buf2;
			}
			break;
		case 'i':
			if (iflags & ITEM_DELETED) {
				n = "*deleting  ";
				break;
			}
			n  = c = buf2 + MAXPATHLEN - 32;
			c[0] = iflags & ITEM_LOCAL_CHANGE
			      ? iflags & ITEM_XNAME_FOLLOWS ? 'h' : 'c'
			     : !(iflags & ITEM_TRANSFER) ? '.'
			     : !local_server && *op == 's' ? '<' : '>';
			if (S_ISLNK(file->mode)) {
				c[1] = 'L';
				c[3] = '.';
				c[4] = !(iflags & ITEM_REPORT_TIME) ? '.'
				     : !preserve_times || !receiver_symlink_times
				    || (iflags & ITEM_REPORT_TIMEFAIL) ? 'T' : 't';
			} else {
				c[1] = S_ISDIR(file->mode) ? 'd'
				     : IS_SPECIAL(file->mode) ? 'S'
				     : IS_DEVICE(file->mode) ? 'D' : 'f';
				c[3] = !(iflags & ITEM_REPORT_SIZE) ? '.' : 's';
				c[4] = !(iflags & ITEM_REPORT_TIME) ? '.'
				     : !preserve_times ? 'T' : 't';
			}
			c[2] = !(iflags & ITEM_REPORT_CHANGE) ? '.' : 'c';
			c[5] = !(iflags & ITEM_REPORT_PERMS) ? '.' : 'p';
			c[6] = !(iflags & ITEM_REPORT_OWNER) ? '.' : 'o';
			c[7] = !(iflags & ITEM_REPORT_GROUP) ? '.' : 'g';
			c[8] = !(iflags & ITEM_REPORT_ATIME) ? '.' : 'u';
			c[9] = !(iflags & ITEM_REPORT_ACL) ? '.' : 'a';
			c[10] = !(iflags & ITEM_REPORT_XATTR) ? '.' : 'x';
			c[11] = '\0';

			if (iflags & (ITEM_IS_NEW|ITEM_MISSING_DATA)) {
				char ch = iflags & ITEM_IS_NEW ? '+' : '?';
				int i;
				for (i = 2; c[i]; i++)
					c[i] = ch;
			} else if (c[0] == '.' || c[0] == 'h' || c[0] == 'c') {
				int i;
				for (i = 2; c[i]; i++) {
					if (c[i] != '.')
						break;
				}
				if (!c[i]) {
					for (i = 2; c[i]; i++)
						c[i] = ' ';
				}
			}
			break;
		}

		/* "n" is the string to be inserted in place of this % code. */
		if (!n)
			continue;
		if (n != buf2 && fmt[1]) {
			strlcat(fmt, "s", sizeof fmt);
			snprintf(buf2, sizeof buf2, fmt, n);
			n = buf2;
		}
		len = strlen(n);

		/* Subtract the length of the escape from the string's size. */
		total -= p - s + 1;

		if (len + total >= (size_t)sizeof buf) {
			rprintf(FERROR,
				"buffer overflow expanding %%%c -- exiting\n",
				p[0]);
			exit_cleanup(RERR_MESSAGEIO);
		}

		/* Shuffle the rest of the string along to make space for n */
		if (len != (size_t)(p - s + 1))
			memmove(s + len, p + 1, total - (s - buf) + 1);
		total += len;

		/* Insert the contents of string "n", but NOT its null. */
		if (len)
			memcpy(s, n, len);

		/* Skip over inserted string; continue looking */
		p = s + len;
	}

	rwrite(code, buf, total, 0);
}