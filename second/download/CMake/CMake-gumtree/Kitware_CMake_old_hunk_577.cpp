			}

		}

		zip_entry->uncompressed_size = zip_entry->compressed_size = 0;

	} else if (0 == (zip_entry->zip_flags & ZIP_LENGTH_AT_END)

	    || zip_entry->uncompressed_size > 0) {

		/* Set the size only if it's meaningful. */

