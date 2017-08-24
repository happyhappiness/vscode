(count--) {
		archive_entry_xattr_next(file->entry,
		    &name, &value, &size);
		checksum_init(&(xar->a_sumwrk), xar->opt_sumalg);
		checksum_init(&(xar->e_sumwrk), xar->opt_sumalg);

		heap = calloc(1, sizeof(*heap));
		if (heap == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for xattr");
			return (ARCHIVE_FATAL);
		}
		heap->id = file->ea_idx++;
		heap->temp_offset = xar->temp_offset;
		heap->size = size;/* save a extracted size */
		heap->compression = xar->opt_compression;
		/* Get a extracted sumcheck value. */
		checksum_update(&(xar->e_sumwrk), value, size);
		checksum_final(&(xar->e_sumwrk), &(heap->e_sum));

		/*
		 * Not compression to xattr is simple way.
		 */
		if (heap->compression == NONE) {
			checksum_update(&(xar->a_sumwrk), value, size);
			checksum_final(&(xar->a_sumwrk), &(heap->a_sum));
			if (write_to_temp(a, value, size)
			    != ARCHIVE_OK) {
				free(heap);
				return (ARCHIVE_FATAL);
			}
			heap->length = size;
			/* Add heap to the tail of file->xattr. */
			heap->next = NULL;
			*file->xattr.last = heap;
			file->xattr.last = &(heap->next);
			/* Next xattr */
			continue;
		}

		/*
		 * Init compression library.
		 */
		r = xar_compression_init_encoder(a);
		if (r != ARCHIVE_OK) {
			free(heap);
			return (ARCHIVE_FATAL);
		}

		xar->stream.next_in = (const unsigned char *)value;
		xar->stream.avail_in = size;
		for (;;) {
			r = compression_code(&(a->archive),
			    &(xar->stream), ARCHIVE_Z_FINISH);
			if (r != ARCHIVE_OK && r != ARCHIVE_EOF) {
				free(heap);
				return (ARCHIVE_FATAL);
			}
			size = sizeof(xar->wbuff) - xar->stream.avail_out;
			checksum_update(&(xar->a_sumwrk),
			    xar->wbuff, size);
			if (write_to_temp(a, xar->wbuff, size)
			    != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			if (r == ARCHIVE_OK) {
				xar->stream.next_out = xar->wbuff;
				xar->stream.avail_out = sizeof(xar->wbuff);
			} else {
				checksum_final(&(xar->a_sumwrk),
				    &(heap->a_sum));
				heap->length = xar->stream.total_out;
				/* Add heap to the tail of file->xattr. */
				heap->next = NULL;
				*file->xattr.last = heap;
				file->xattr.last = &(heap->next);
				break;
			}
		}
		/* Clean up compression library. */
		r = compression_end(&(a->archive), &(xar->stream));
		if (r != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	}