{
		// Save the positions so that we can restore them in case
		// an error occurs.
		const size_t in_start = *in_pos;
		const size_t out_start = *out_pos;

		// Do the actual decoding.
		ret = stream_decoder.code(stream_decoder.coder, allocator,
				in, in_pos, in_size, out, out_pos, out_size,
				LZMA_FINISH);

		if (ret == LZMA_STREAM_END) {
			ret = LZMA_OK;
		} else {
			// Something went wrong, restore the positions.
			*in_pos = in_start;
			*out_pos = out_start;

			if (ret == LZMA_OK) {
				// Either the input was truncated or the
				// output buffer was too small.
				assert(*in_pos == in_size
						|| *out_pos == out_size);

				// If all the input was consumed, then the
				// input is truncated, even if the output
				// buffer is also full. This is because
				// processing the last byte of the Stream
				// never produces output.
				if (*in_pos == in_size)
					ret = LZMA_DATA_ERROR;
				else
					ret = LZMA_BUF_ERROR;

			} else if (ret == LZMA_MEMLIMIT_ERROR) {
				// Let the caller know how much memory would
				// have been needed.
				uint64_t memusage;
				(void)stream_decoder.memconfig(
						stream_decoder.coder,
						memlimit, &memusage, 0);
			}
		}
	}