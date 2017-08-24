{
			r = get_str_opt(a,
			    &(iso9660->application_identifier),
			    APPLICATION_IDENTIFIER_SIZE, key, value);
			iso9660->opt.application_id = r == ARCHIVE_OK;
			return (r);
		}