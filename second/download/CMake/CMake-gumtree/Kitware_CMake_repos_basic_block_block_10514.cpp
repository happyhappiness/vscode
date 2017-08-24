{
		*p = state->out_block;
		if (self->code == ARCHIVE_FILTER_LZIP) {
			state->crc32 = lzma_crc32(state->out_block,
			    decompressed, state->crc32);
			if (state->eof) {
				ret = lzip_tail(self);
				if (ret != ARCHIVE_OK)
					return (ret);
			}
		}
	}