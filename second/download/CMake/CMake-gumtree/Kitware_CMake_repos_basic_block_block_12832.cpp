{
		/* Parse decimal length field at start of line. */
		line_length = 0;
		l = attr_length;
		p = attr; /* Record start of line. */
		while (l>0) {
			if (*p == ' ') {
				p++;
				l--;
				break;
			}
			if (*p < '0' || *p > '9') {
				archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
				    "Ignoring malformed pax extended attributes");
				return (ARCHIVE_WARN);
			}
			line_length *= 10;
			line_length += *p - '0';
			if (line_length > 999999) {
				archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
				    "Rejecting pax extended attribute > 1MB");
				return (ARCHIVE_WARN);
			}
			p++;
			l--;
		}

		/*
		 * Parsed length must be no bigger than available data,
		 * at least 1, and the last character of the line must
		 * be '\n'.
		 */
		if (line_length > attr_length
		    || line_length < 1
		    || attr[line_length - 1] != '\n')
		{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Ignoring malformed pax extended attribute");
			return (ARCHIVE_WARN);
		}

		/* Null-terminate the line. */
		attr[line_length - 1] = '\0';

		/* Find end of key and null terminate it. */
		key = p;
		if (key[0] == '=')
			return (-1);
		while (*p && *p != '=')
			++p;
		if (*p == '\0') {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Invalid pax extended attributes");
			return (ARCHIVE_WARN);
		}
		*p = '\0';

		value = p + 1;

		/* Some values may be binary data */
		value_length = attr + line_length - 1 - value;

		/* Identify this attribute and set it in the entry. */
		err2 = pax_attribute(a, tar, entry, key, value, value_length);
		if (err2 == ARCHIVE_FATAL)
			return (err2);
		err = err_combine(err, err2);

		/* Skip to next line */
		attr += line_length;
		attr_length -= line_length;
	}