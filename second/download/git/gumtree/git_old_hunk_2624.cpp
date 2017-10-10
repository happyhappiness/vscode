			    git_path("sharedindex.%s",
				     sha1_to_hex(split_index->base_sha1)), 1);
	if (hashcmp(split_index->base_sha1, split_index->base->sha1))
		die("broken index, expect %s in %s, got %s",
		    sha1_to_hex(split_index->base_sha1),
		    git_path("sharedindex.%s",
				     sha1_to_hex(split_index->base_sha1)),
		    sha1_to_hex(split_index->base->sha1));
	merge_base_index(istate);
	check_ce_order(istate);
	return ret;
}

