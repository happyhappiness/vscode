(ret == LZMA_OK) {
		// Save the positions so that we can restore them in case
		// an error occurs.
		const size_t in_start = *in_pos;
		const size_t out_start = *out_pos;

		// Do the actual decoding.
		ret = block_decoder.code(block_decoder.coder, allocator,
				in, in_pos, in_size, out, out_pos, out_size,
				LZMA_FINISH);

		if (ret == LZMA_STREAM_END) {
			ret = LZMA_OK;
		} else {
			if (ret == LZMA_OK) {
				// Either the input was truncated or the
				// output buffer was too small.
				assert(*in_pos == in_size
						|| *out_pos == out_size);

				// If all the input was consumed, then the
				// input is truncated, even if the output
				// buffer is also full. This is because
				// processing the last byte of the Block
				// never produces output.
				//
				// NOTE: This assumption may break when new
				// filters are added, if the end marker of
				// the filter doesn't consume at least one
				// complete byte.
				if (*in_pos == in_size)
					ret = LZMA_DATA_ERROR;
				else
					ret = LZMA_BUF_ERROR;
			}

			// Restore the positions.
			*in_pos = in_start;
			*out_pos = out_start;
		}
	}