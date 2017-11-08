void set_compression(char *fname)
{
	extern int module_id;
	char *dont;
	char *tok;

	if (!do_compression) return;

	compression_level = Z_DEFAULT_COMPRESSION;
	dont = lp_dont_compress(module_id);

	if (!dont || !*dont) return;

	if ((dont[0] == '*') && (!dont[1])) {
		/* an optimization to skip the rest of this routine */
		compression_level = 0;
		return;
	}

	dont = strdup(dont);
	fname = strdup(fname);
	if (!dont || !fname) return;

	strlower(dont);
	strlower(fname);

	for (tok=strtok(dont," ");tok;tok=strtok(NULL," ")) {
		if (wildmatch(tok, fname)) {
			compression_level = 0;
			break;
		}
	}
	free(dont);
	free(fname);
}