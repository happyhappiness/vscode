{
		uint64_t* aligned_message_block;
		if (IS_ALIGNED_64(msg)) {
			/* the most common case is processing of an already aligned message
			without copying it */
			aligned_message_block = (uint64_t*)msg;
		} else {
			memcpy(ctx->message, msg, sha512_block_size);
			aligned_message_block = ctx->message;
		}

		rhash_sha512_process_block(ctx->hash, aligned_message_block);
		msg  += sha512_block_size;
		size -= sha512_block_size;
	}