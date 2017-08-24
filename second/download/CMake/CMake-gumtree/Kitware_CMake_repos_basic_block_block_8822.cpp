{
			if (sp->offset + sp->length + length < 0)
				/* A value of "length" parameter is
				 * too large. */
				return;
			/* Expand existing sparse block size. */
			sp->length += length;
			return;
		}