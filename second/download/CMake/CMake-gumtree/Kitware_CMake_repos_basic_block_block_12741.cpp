{
			/* Try to consume a second all-null record, as well. */
			tar_flush_unconsumed(a, unconsumed);
			h = __archive_read_ahead(a, 512, NULL);
			if (h != NULL && h[0] == 0 && archive_block_is_null(h))
				__archive_read_consume(a, 512);
			archive_clear_error(&a->archive);
			return (ARCHIVE_EOF);
		}