static int parse_one_option(const char *option)
{
	if (starts_with(option, "max-pack-size=")) {
		unsigned long v;
		if (!git_parse_ulong(option + 14, &v))
			return 0;
		if (v < 8192) {
			warning("max-pack-size is now in bytes, assuming --max-pack-size=%lum", v);
			v *= 1024 * 1024;
		} else if (v < 1024 * 1024) {
			warning("minimum max-pack-size is 1 MiB");
			v = 1024 * 1024;
		}
		max_packsize = v;
	} else if (starts_with(option, "big-file-threshold=")) {
		unsigned long v;
		if (!git_parse_ulong(option + 19, &v))
			return 0;
		big_file_threshold = v;
	} else if (starts_with(option, "depth=")) {
		option_depth(option + 6);
	} else if (starts_with(option, "active-branches=")) {
		option_active_branches(option + 16);
	} else if (starts_with(option, "export-pack-edges=")) {
		option_export_pack_edges(option + 18);
	} else if (starts_with(option, "quiet")) {
		show_stats = 0;
	} else if (starts_with(option, "stats")) {
		show_stats = 1;
	} else {
		return 0;
	}

	return 1;
}