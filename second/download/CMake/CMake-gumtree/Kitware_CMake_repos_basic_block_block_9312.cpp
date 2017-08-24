{
		struct archive_read_filter *t = f->upstream;
		if (!f->closed && f->close != NULL) {
			int r1 = (f->close)(f);
			f->closed = 1;
			if (r1 < r)
				r = r1;
		}
		free(f->buffer);
		f->buffer = NULL;
		f = t;
	}