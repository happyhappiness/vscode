static void patch_id_add_mode(git_SHA_CTX *ctx, unsigned mode)
{
	/* large enough for 2^32 in octal */
	char buf[12];
	int len = xsnprintf(buf, sizeof(buf), "%06o", mode);
	git_SHA1_Update(ctx, buf, len);
}