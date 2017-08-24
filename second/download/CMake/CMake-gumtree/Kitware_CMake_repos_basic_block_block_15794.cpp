{
			r = get_str_opt(a,
			    &(iso9660->publisher_identifier),
			    PUBLISHER_IDENTIFIER_SIZE, key, value);
			iso9660->opt.publisher = r == ARCHIVE_OK;
			return (r);
		}