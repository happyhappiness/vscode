printf("%s%s--- %s%s%s\n", prefix, c_meta,
	       pair->one->sha1_valid ? "a/" : "",
	       pair->one->sha1_valid ? pair->one->path : "/dev/null",
	       c_reset);