static void setup_commit_formats(void)
{
	struct cmt_fmt_map builtin_formats[] = {
		{ "raw",	CMIT_FMT_RAW,		0,	0 },
		{ "medium",	CMIT_FMT_MEDIUM,	0,	8 },
		{ "short",	CMIT_FMT_SHORT,		0,	0 },
		{ "email",	CMIT_FMT_EMAIL,		0,	0 },
		{ "mboxrd",	CMIT_FMT_MBOXRD,	0,	0 },
		{ "fuller",	CMIT_FMT_FULLER,	0,	8 },
		{ "full",	CMIT_FMT_FULL,		0,	8 },
		{ "oneline",	CMIT_FMT_ONELINE,	1,	0 }
	};
	commit_formats_len = ARRAY_SIZE(builtin_formats);
	builtin_formats_len = commit_formats_len;
	ALLOC_GROW(commit_formats, commit_formats_len, commit_formats_alloc);
	memcpy(commit_formats, builtin_formats,
	       sizeof(*builtin_formats)*ARRAY_SIZE(builtin_formats));

	git_config(git_pretty_formats_config, NULL);
}