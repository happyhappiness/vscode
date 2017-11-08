static void patch_id_consume(void *priv, char *line, unsigned long len)
{
	struct patch_id_t *data = priv;
	int new_len;

	/* Ignore line numbers when computing the SHA1 of the patch */
	if (starts_with(line, "@@ -"))
		return;

	new_len = remove_space(line, len);

	git_SHA1_Update(data->ctx, line, new_len);
	data->patchlen += new_len;
}