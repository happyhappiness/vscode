(strcmp(key, "abstract-file") == 0) {
			r = get_str_opt(a,
			    &(iso9660->abstract_file_identifier),
			    ABSTRACT_FILE_SIZE, key, value);
			iso9660->opt.abstract_file = r == ARCHIVE_OK;
			return (r);
		}