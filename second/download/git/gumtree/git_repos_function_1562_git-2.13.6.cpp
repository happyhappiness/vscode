static void patch_id_add_string(git_SHA_CTX *ctx, const char *str)
{
	git_SHA1_Update(ctx, str, strlen(str));
}