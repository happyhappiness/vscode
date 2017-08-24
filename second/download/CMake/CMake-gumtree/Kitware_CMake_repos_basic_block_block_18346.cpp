{
			le32_copy(ctx->message, 0, msg, md5_block_size);
			aligned_message_block = ctx->message;
		}