		ret = child_write(f, data, buf, length);
		if (ret == -1 || ret == 0) {
			archive_set_error(f->archive, EIO,
			    "Can't write to program: %s", data->program_name);
			return (ARCHIVE_FATAL);
		}
		length -= ret;
