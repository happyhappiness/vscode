	} else {
		file_parent.ptr = "";
		file_parent.size = 0;
	}

	diff_ranges_init(&diff);
	collect_diff(&file_parent, &file_target, &diff);

	/* NEEDSWORK should apply some heuristics to prevent mismatches */
	free(rg->path);
	rg->path = xstrdup(pair->one->path);

	range_set_init(&tmp, 0);
