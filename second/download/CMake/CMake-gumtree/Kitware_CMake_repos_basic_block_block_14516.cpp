{
		if (value == NULL || !(value[0] >= '4' && value[0] <= '7') ||
		    value[1] != '\0')
			return (ARCHIVE_WARN);
		data->block_maximum_size = value[0] - '0';
		return (ARCHIVE_OK);
	}