{
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

			}