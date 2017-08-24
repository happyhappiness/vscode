{
				struct content *con;

				if (multi == NULL) {
					multi = child;
					multi->contents.first = NULL;
					multi->contents.last =
					    &(multi->contents.first);
				}
				con = malloc(sizeof(struct content));
				if (con == NULL) {
					archive_set_error(
					    &a->archive, ENOMEM,
					    "No memory for multi extent");
					__archive_read_consume(a, skip_size);
					return (ARCHIVE_FATAL);
				}
				con->offset = child->offset;
				con->size = child->size;
				con->next = NULL;
				*multi->contents.last = con;
				multi->contents.last = &(con->next);
				if (multi == child) {
					if (add_entry(a, iso9660, child)
					    != ARCHIVE_OK)
						return (ARCHIVE_FATAL);
				} else {
					multi->size += child->size;
					if (!child->multi_extent)
						multi = NULL;
				}
			}