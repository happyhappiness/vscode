{
		// Calculate the integrity check. We reserved space for
		// the Check field earlier so we don't need to check for
		// available output space here.
		lzma_check_state check;
		lzma_check_init(&check, block->check);
		lzma_check_update(&check, block->check, in, in_size);
		lzma_check_finish(&check, block->check);

		memcpy(block->raw_check, check.buffer.u8, check_size);
		memcpy(out + *out_pos, check.buffer.u8, check_size);
		*out_pos += check_size;
	}