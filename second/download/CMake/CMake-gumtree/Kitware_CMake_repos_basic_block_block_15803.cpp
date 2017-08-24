{
			r = get_str_opt(a,
			    &(iso9660->copyright_file_identifier),
			    COPYRIGHT_FILE_SIZE, key, value);
			iso9660->opt.copyright_file = r == ARCHIVE_OK;
			return (r);
		}