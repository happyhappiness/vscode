{
		tar_flush_unconsumed(a, unconsumed);
		archive_set_error(&a->archive, EINVAL, "Too many special headers");
		return (ARCHIVE_WARN);
	}