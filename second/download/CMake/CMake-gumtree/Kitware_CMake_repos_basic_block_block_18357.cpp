{
		unsigned* aligned_message_block;
		if (IS_ALIGNED_32(msg)) {
			/* the most common case is processing of an already aligned message
			without copying it */
			aligned_message_block = (unsigned*)msg;
		} else {
			memcpy(ctx->message, msg, sha256_block_size);
			aligned_message_block = (unsigned*)ctx->message;
		}

		rhash_sha256_process_block(ctx->hash, aligned_message_block);
		msg  += sha256_block_size;
		size -= sha256_block_size;
	}