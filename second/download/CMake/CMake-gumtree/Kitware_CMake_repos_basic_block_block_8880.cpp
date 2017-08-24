{
			const char *s = (const char *)b;
			size_t length = 0;
			int found_separator = 0;

			while (length < size) {
				if (nullSeparator) {
					if (*b == '\0') {
						found_separator = 1;
						break;
					}
				} else {
			            	if (*b == 0x0d || *b == 0x0a) {
						found_separator = 1;
						break;
					}
				}
				b++;
				length++;
			}
			if (!found_separator) {
				archive_strncat(&as, s, length);
				/* Read next data block. */
				break;
			}
			b++;
			size -= length + 1;
			archive_strncat(&as, s, length);

			/* If the line is not empty, add the pattern. */
			if (archive_strlen(&as) > 0) {
				/* Add pattern. */
				r = add_pattern_mbs(a, mlist, as.s);
				if (r != ARCHIVE_OK) {
					archive_read_free(ar);
					archive_string_free(&as);
					return (r);
				}
				archive_string_empty(&as);
			}
		}