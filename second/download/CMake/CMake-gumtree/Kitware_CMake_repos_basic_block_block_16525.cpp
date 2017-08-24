{
		free(iso9660->zisofs.block_pointers);
		iso9660->zisofs.block_pointers = malloc(bpsize);
		if (iso9660->zisofs.block_pointers == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate data");
			return (ARCHIVE_FATAL);
		}
		iso9660->zisofs.block_pointers_allocated = bpsize;
	}