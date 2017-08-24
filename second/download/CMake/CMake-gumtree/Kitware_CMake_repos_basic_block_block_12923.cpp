{
		e = p;
		while (*e != '\0' && *e != ',') {
			if (*e < '0' || *e > '9')
				return (ARCHIVE_WARN);
			e++;
		}
		if (offset < 0) {
			offset = tar_atol10(p, e - p);
			if (offset < 0)
				return (ARCHIVE_WARN);
		} else {
			size = tar_atol10(p, e - p);
			if (size < 0)
				return (ARCHIVE_WARN);
			if (gnu_add_sparse_entry(a, tar, offset, size)
			    != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			offset = -1;
		}
		if (*e == '\0')
			return (ARCHIVE_OK);
		p = e + 1;
	}