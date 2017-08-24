{
		unsigned left = md5_block_size - index;
		le32_copy((char*)ctx->message, index, msg, (size < left ? size : left));
		if (size < left) return;

		/* process partial block */
		rhash_md5_process_block(ctx->hash, ctx->message);
		msg  += left;
		size -= left;
	}