(data->threads == 0 && errno != 0) {
			data->threads = 1;
			return (ARCHIVE_WARN);
		}