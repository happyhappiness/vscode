{
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