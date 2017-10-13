fprintf(opt->file, "%s%s--- %s%s%s\n", prefix, c_meta,
	       pair->one->oid_valid ? "a/" : "",
	       pair->one->oid_valid ? pair->one->path : "/dev/null",
	       c_reset);