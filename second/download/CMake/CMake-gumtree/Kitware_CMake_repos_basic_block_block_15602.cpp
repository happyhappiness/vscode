{
			/*
			 * For filename longer than 15 bytes, GNU variant
			 * makes use of a string table and instead stores the
			 * offset of the real filename to in the ar_name field.
			 * The string table should have been written before.
			 */
			if (ar->has_strtab <= 0) {
				archive_set_error(&a->archive, EINVAL,
				    "Can't find string table");
				return (ARCHIVE_WARN);
			}

			se = (char *)malloc(strlen(filename) + 3);
			if (se == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate filename buffer");
				return (ARCHIVE_FATAL);
			}

			strncpy(se, filename, strlen(filename));
			strcpy(se + strlen(filename), "/\n");

			ss = strstr(ar->strtab, se);
			free(se);

			if (ss == NULL) {
				archive_set_error(&a->archive, EINVAL,
				    "Invalid string table");
				return (ARCHIVE_WARN);
			}

			/*
			 * GNU variant puts "/" followed by digits into
			 * ar_name field. These digits indicates the real
			 * filename string's offset to the string table.
			 */
			buff[AR_name_offset] = '/';
			if (format_decimal(ss - ar->strtab,
			    buff + AR_name_offset + 1,
			    AR_name_size - 1)) {
				archive_set_error(&a->archive, ERANGE,
				    "string table offset too large");
				return (ARCHIVE_WARN);
			}
		}