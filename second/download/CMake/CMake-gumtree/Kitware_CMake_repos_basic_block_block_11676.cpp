{
			size_t alloc;

			if (zisofs->block_pointers != NULL)
				free(zisofs->block_pointers);
			alloc = ((xsize >> 10) + 1) << 10;
			zisofs->block_pointers = malloc(alloc);
			if (zisofs->block_pointers == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "No memory for zisofs decompression");
				return (ARCHIVE_FATAL);
			}
			zisofs->block_pointers_alloc = alloc;
		}