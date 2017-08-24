{
		e = p;
		while (*e != '\0' && *e != ' ') {
			if (*e < '0' || *e > '9')
				return (ARCHIVE_WARN);
			e++;
		}
		start = end;
		end = tar_atol10(p, e - p);
		if (end < 0)
			return (ARCHIVE_WARN);
		if (start < end) {
			if (gnu_add_sparse_entry(a, tar, start,
			    end - start) != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			tar->sparse_last->hole = hole;
		}
		if (*e == '\0')
			return (ARCHIVE_OK);
		p = e + 1;
		hole = hole == 0;
	}