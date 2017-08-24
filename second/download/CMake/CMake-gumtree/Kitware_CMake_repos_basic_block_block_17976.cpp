{
				// All the input was consumed and output
				// buffer is full. Now we don't immediately
				// know the reason for the error. Try
				// decoding one more byte. If it succeeds,
				// then the output buffer was too small. If
				// we cannot get a new output byte, the input
				// is truncated.
				uint8_t tmp[1];
				size_t tmp_pos = 0;
				(void)next.code(next.coder, allocator,
						in, in_pos, in_size,
						tmp, &tmp_pos, 1, LZMA_FINISH);

				if (tmp_pos == 1)
					ret = LZMA_BUF_ERROR;
				else
					ret = LZMA_DATA_ERROR;
			}