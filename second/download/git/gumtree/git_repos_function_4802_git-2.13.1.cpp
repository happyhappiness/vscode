void SHA1DCSetCallback(SHA1_CTX* ctx, collision_block_callback callback)
{
	ctx->callback = callback;
}