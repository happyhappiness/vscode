void precompose_argv(int argc, const char **argv)
{
	int i = 0;
	const char *oldarg;
	char *newarg;
	iconv_t ic_precompose;

	if (precomposed_unicode != 1)
		return;

	ic_precompose = iconv_open(repo_encoding, path_encoding);
	if (ic_precompose == (iconv_t) -1)
		return;

	while (i < argc) {
		size_t namelen;
		oldarg = argv[i];
		if (has_non_ascii(oldarg, (size_t)-1, &namelen)) {
			newarg = reencode_string_iconv(oldarg, namelen, ic_precompose, NULL);
			if (newarg)
				argv[i] = newarg;
		}
		i++;
	}
	iconv_close(ic_precompose);
}