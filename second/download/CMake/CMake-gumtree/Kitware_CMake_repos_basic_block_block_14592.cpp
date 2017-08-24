{
		archive_strappend_char(&as, ' ');
		archive_strappend_char(&as, '-');
		archive_strappend_char(&as, '0' + data->compression_level);
	}