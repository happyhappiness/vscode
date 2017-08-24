((int64_t)file->offset + (int64_t)file->uncompressed_size
		    > ARCHIVE_LITERAL_LL(0x7FFF8000))
			goto invalid;