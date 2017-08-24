{
			if (__archive_read_consume(a, tar->entry_padding) < 0)
				return (ARCHIVE_FATAL);
			tar->entry_padding = 0;
			*buff = NULL;
			*size = 0;
			*offset = tar->realsize;
			return (ARCHIVE_EOF);
		}