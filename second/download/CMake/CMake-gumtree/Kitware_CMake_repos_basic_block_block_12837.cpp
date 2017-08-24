{
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