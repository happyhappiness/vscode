(iso9660->current_position < file->offset) {
		int64_t step;

		step = file->offset - iso9660->current_position;
		step = __archive_read_consume(a, step);
		if (step < 0)
			return ((int)step);
		iso9660->current_position = file->offset;
	}