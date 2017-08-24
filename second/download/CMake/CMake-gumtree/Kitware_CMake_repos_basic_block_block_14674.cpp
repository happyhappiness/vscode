{
		if (value == NULL || !(value[0] >= '0' && value[0] <= '9') ||
		    value[1] != '\0')
			return (ARCHIVE_WARN);
		data->compression_level = value[0] - '0';
		if (data->compression_level > 6)
			data->compression_level = 6;
		return (ARCHIVE_OK);
	}