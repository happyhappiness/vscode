(p = tar->sparse_list; p != NULL; p = p->next) {
		if (!p->hole) {
			if (p->remaining >= INT64_MAX - request) {
				return ARCHIVE_FATAL;
			}
			request += p->remaining;
		}
	}