{
			strncpy(buff + AR_name_offset, "#1/", 3);
			if (format_decimal(strlen(filename),
			    buff + AR_name_offset + 3,
			    AR_name_size - 3)) {
				archive_set_error(&a->archive, ERANGE,
				    "File name too long");
				return (ARCHIVE_WARN);
			}
			append_fn = 1;
			size += strlen(filename);
		}