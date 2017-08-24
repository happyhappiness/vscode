{
		ret = __archive_write_output(
			a, mtree->buf.s, mtree->buf.length);
		archive_string_empty(&mtree->buf);
	}