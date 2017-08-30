	}



	iso9660->entry_bytes_remaining = file->size;

	iso9660->entry_sparse_offset = 0; /* Offset for sparse-file-aware clients. */



	if (file->offset + file->size > iso9660->volume_size) {

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "File is beyond end-of-media: %s",

		    archive_entry_pathname(entry));

		iso9660->entry_bytes_remaining = 0;

		iso9660->entry_sparse_offset = 0;

		return (ARCHIVE_WARN);

	}



