{
			new_block = malloc(MAX_DECMPFS_XATTR_SIZE
			    + sizeof(uint32_t));
			if (new_block == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory for decmpfs");
				return (ARCHIVE_FATAL);
			}
			a->decmpfs_header_p = new_block;
		}