{
		size_t left = sha512_block_size - index;
		memcpy((char*)ctx->message + index, msg, (size < left ? size : left));
		if (size < left) return;

		/* process partial block */
		rhash_sha512_process_block(ctx->hash, ctx->message);
		msg  += left;
		size -= left;
	}