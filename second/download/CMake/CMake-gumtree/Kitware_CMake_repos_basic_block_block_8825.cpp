((sp = entry->sparse_tail) != NULL) {
		if (sp->offset + sp->length > offset)
			/* Invalid value. */
			return;
		if (sp->offset + sp->length == offset) {
			if (sp->offset + sp->length + length < 0)
				/* A value of "length" parameter is
				 * too large. */
				return;
			/* Expand existing sparse block size. */
			sp->length += length;
			return;
		}
	}