static void log_formatted(enum logcode code, char *format, char *op,
			  struct file_struct *file, struct stats *initial_stats,
			  int iflags, char *hlink)
{
	char buf[MAXPATHLEN+1024], buf2[MAXPATHLEN], fmt[32];
	char *p, *s, *n;
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
		s = p++;
		n = fmt + 1;
		if (*p == '-')
			*n++ = *p++;
		while (isdigit(*(uchar*)p) && n - fmt < (int)(sizeof fmt) - 8)
			*n++ = *p++;
		if (!*p)
			break;
		*n = '\0';
		n = NULL;

		switch (*p) {
		case 'h':
			if (am_daemon)
				n = client_name(0);
			break;
		case 'a':
			if (am_daemon)
				n = client_addr(0);
			break;
		case 'l':
			strlcat(fmt, ".0f", sizeof fmt);
			snprintf(buf2, sizeof buf2, fmt,
				 (double)file->length);
			n = buf2;
			break;
		case 'U':
			strlcat(fmt, "ld", sizeof fmt);
			snprintf(buf2, sizeof buf2, fmt,
				 (long)file->uid);
			n = buf2;
			break;
		case 'G':
			if (file->gid == GID_NONE)
				n = "DEFAULT";
			else {
				strlcat(fmt, "ld", sizeof fmt);
				snprintf(buf2, sizeof buf2, fmt,
					 (long)file->gid);
				n = buf2;
			}
			break;
		case 'p':
			strlcat(fmt, "ld", sizeof fmt);
			snprintf(buf2, sizeof buf2, fmt,
				 (long)getpid());
			n = buf2;
			break;
		case 'M':
			n = timestring(file->modtime);
			{
				char *cp = n;
				while ((cp = strchr(cp, ' ')) != NULL)
					*cp = '-';
			}
			break;
		case 'B':
			n = buf2 + MAXPATHLEN - PERMSTRING_SIZE;
			permstring(n - 1, file->mode); /* skip the type char */
			break;
		case 'o':
			n = op;
			break;
		case 'f':
			n = f_name(file, NULL);
			if (am_sender && file->dir.root) {
				pathjoin(buf2, sizeof buf2,
					 file->dir.root, n);
				clean_fname(buf2, 0);
				if (fmt[1])
					strlcpy(n, buf2, MAXPATHLEN);
				else
					n = buf2;
			} else if (*n != '/') {
				pathjoin(buf2, sizeof buf2,
					 curr_dir + module_dirlen, n);
				clean_fname(buf2, 0);
				if (fmt[1])
					strlcpy(n, buf2, MAXPATHLEN);
				else
					n = buf2;
			} else
				clean_fname(n, 0);
			if (*n == '/')
				n++;
			break;
		case 'n':
			n = f_name(file, NULL);
			if (S_ISDIR(file->mode))
				strlcat(n, "/", MAXPATHLEN);
			break;
		case 'L':
			if (hlink && *hlink) {
				n = hlink;
				strlcpy(buf2, " => ", sizeof buf2);
			} else if (S_ISLNK(file->mode) && file->u.link) {
				n = file->u.link;
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
			n = lp_path(module_id);
			break;
		case 'u':
			n = auth_user;
			break;
		case 'b':
			if (am_sender) {
				b = stats.total_written -
					initial_stats->total_written;
			} else {
				b = stats.total_read -
					initial_stats->total_read;
			}
			strlcat(fmt, ".0f", sizeof fmt);
			snprintf(buf2, sizeof buf2, fmt, (double)b);
			n = buf2;
			break;
		case 'c':
			if (!am_sender) {
				b = stats.total_written -
					initial_stats->total_written;
			} else {
				b = stats.total_read -
					initial_stats->total_read;
			}
			strlcat(fmt, ".0f", sizeof fmt);
			snprintf(buf2, sizeof buf2, fmt, (double)b);
			n = buf2;
			break;
		case 'i':
			if (iflags & ITEM_DELETED) {
				n = "*deleting";
				break;
			}
			n = buf2 + MAXPATHLEN - 32;
			n[0] = iflags & ITEM_LOCAL_CHANGE
			      ? iflags & ITEM_XNAME_FOLLOWS ? 'h' : 'c'
			     : !(iflags & ITEM_TRANSFER) ? '.'
			     : !local_server && *op == 's' ? '<' : '>';
			n[1] = S_ISDIR(file->mode) ? 'd'
			     : IS_SPECIAL(file->mode) ? 'S'
			     : IS_DEVICE(file->mode) ? 'D'
			     : S_ISLNK(file->mode) ? 'L' : 'f';
			n[2] = !(iflags & ITEM_REPORT_CHECKSUM) ? '.' : 'c';
			n[3] = !(iflags & ITEM_REPORT_SIZE) ? '.' : 's';
			n[4] = !(iflags & ITEM_REPORT_TIME) ? '.'
			     : !preserve_times || S_ISLNK(file->mode) ? 'T' : 't';
			n[5] = !(iflags & ITEM_REPORT_PERMS) ? '.' : 'p';
			n[6] = !(iflags & ITEM_REPORT_OWNER) ? '.' : 'o';
			n[7] = !(iflags & ITEM_REPORT_GROUP) ? '.' : 'g';
			n[8] = '.';
			n[9] = '\0';

			if (iflags & (ITEM_IS_NEW|ITEM_MISSING_DATA)) {
				char ch = iflags & ITEM_IS_NEW ? '+' : '?';
				int i;
				for (i = 2; n[i]; i++)
					n[i] = ch;
			} else if (n[0] == '.' || n[0] == 'h'
			        || (n[0] == 'c' && n[1] == 'f')) {
				int i;
				for (i = 2; n[i]; i++) {
					if (n[i] != '.')
						break;
				}
				if (!n[i]) {
					for (i = 2; n[i]; i++)
						n[i] = ' ';
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

	rwrite(code, buf, total);
}