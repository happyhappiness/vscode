		ret = child_write(f, data, buf, length);

		if (ret == -1 || ret == 0) {

			archive_set_error(f->archive, EIO,

			    "Can't write to filter");

			return (ARCHIVE_FATAL);

		}

		length -= ret;

