(iso9660->current_position < iso9660->entry_content->offset) {
			int64_t step;

			step = iso9660->entry_content->offset -
			    iso9660->current_position;
			step = __archive_read_consume(a, step);
			if (step < 0)
				return ((int)step);
			iso9660->current_position =
			    iso9660->entry_content->offset;
		}