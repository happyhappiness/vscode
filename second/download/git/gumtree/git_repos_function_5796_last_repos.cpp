static int batch_option_callback(const struct option *opt,
				 const char *arg,
				 int unset)
{
	struct batch_options *bo = opt->value;

	if (bo->enabled) {
		return 1;
	}

	bo->enabled = 1;
	bo->print_contents = !strcmp(opt->long_name, "batch");
	bo->format = arg;

	return 0;
}