{
			r = get_str_opt(a, &(iso9660->volume_identifier),
			    VOLUME_IDENTIFIER_SIZE, key, value);
			iso9660->opt.volume_id = r == ARCHIVE_OK;
			return (r);
		}