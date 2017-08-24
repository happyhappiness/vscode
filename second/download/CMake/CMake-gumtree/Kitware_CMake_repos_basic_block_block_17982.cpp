{
		if (ret == LZMA_OK) {
			// Output buffer was too small.
			assert(*out_pos == out_size);
			ret = LZMA_BUF_ERROR;
		}

		// Restore the output position.
		*out_pos = out_start;
	}