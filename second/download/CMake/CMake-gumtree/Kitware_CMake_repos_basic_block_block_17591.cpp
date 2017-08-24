{
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