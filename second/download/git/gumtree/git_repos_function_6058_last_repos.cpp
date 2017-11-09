static int cacheinfo_callback(struct parse_opt_ctx_t *ctx,
				const struct option *opt, int unset)
{
	struct object_id oid;
	unsigned int mode;
	const char *path;

	if (!parse_new_style_cacheinfo(ctx->argv[1], &mode, &oid, &path)) {
		if (add_cacheinfo(mode, &oid, path, 0))
			die("git update-index: --cacheinfo cannot add %s", path);
		ctx->argv++;
		ctx->argc--;
		return 0;
	}
	if (ctx->argc <= 3)
		return error("option 'cacheinfo' expects <mode>,<sha1>,<path>");
	if (strtoul_ui(*++ctx->argv, 8, &mode) ||
	    get_oid_hex(*++ctx->argv, &oid) ||
	    add_cacheinfo(mode, &oid, *++ctx->argv, 0))
		die("git update-index: --cacheinfo cannot add %s", *ctx->argv);
	ctx->argc -= 3;
	return 0;
}