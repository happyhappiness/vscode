{
			ret = lzma_index_buffer_encode(
					i, out, &out_pos, out_size);

			stream_flags.backward_size = lzma_index_size(i);
		}