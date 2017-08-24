{
					/* Regular file entry. */
					__archive_read_consume(a, skipped);
					return zip_read_local_file_header(a,
					    entry, zip);
				}