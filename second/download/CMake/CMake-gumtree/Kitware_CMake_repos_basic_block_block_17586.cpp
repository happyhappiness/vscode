{
				checksum_final(&(xar->a_sumwrk),
				    &(heap->a_sum));
				heap->length = xar->stream.total_out;
				/* Add heap to the tail of file->xattr. */
				heap->next = NULL;
				*file->xattr.last = heap;
				file->xattr.last = &(heap->next);
				break;
			}