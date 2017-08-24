{
			memcpy(ctx->message, msg, sha256_block_size);
			aligned_message_block = (unsigned*)ctx->message;
		}