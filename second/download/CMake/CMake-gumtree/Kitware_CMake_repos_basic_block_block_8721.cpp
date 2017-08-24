(*s == '"') {
			ssize_t q = extract_quotation(as, s);
			if (q < 0)
				return (ARCHIVE_FAILED);/* Invalid sequence. */
			s += q;
		}