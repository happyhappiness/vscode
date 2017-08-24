{
		unsigned* aligned_message_block;
		if (IS_LITTLE_ENDIAN && IS_ALIGNED_32(msg)) {
			/* the most common case is processing a 32-bit aligned message
			on a little-endian CPU without copying it */
			aligned_message_block = (unsigned*)msg;
		} else {
			le32_copy(ctx->message, 0, msg, md5_block_size);
			aligned_message_block = ctx->message;
		}

		rhash_md5_process_block(ctx->hash, aligned_message_block);
		msg  += md5_block_size;
		size -= md5_block_size;
	}