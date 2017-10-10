			git_die_config("pack.indexversion",
					"bad pack.indexversion=%"PRIu32, pack_idx_opts.version);
	}
	if (!git_config_get_ulong("pack.packsizelimit", &packsizelimit_value))
		max_packsize = packsizelimit_value;

	if (!git_config_get_int("fastimport.unpacklimit", &limit))
		unpack_limit = limit;
	else if (!git_config_get_int("transfer.unpacklimit", &limit))
		unpack_limit = limit;

	git_config(git_default_config, NULL);
}

static const char fast_import_usage[] =
"git fast-import [--date-format=<f>] [--max-pack-size=<n>] [--big-file-threshold=<n>] [--depth=<n>] [--active-branches=<n>] [--export-marks=<marks.file>]";

