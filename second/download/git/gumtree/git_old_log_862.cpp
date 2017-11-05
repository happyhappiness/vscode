die("broken index, expect %s in %s, got %s",
		    sha1_to_hex(split_index->base_sha1),
		    git_path("sharedindex.%s",
			     sha1_to_hex(split_index->base_sha1)),
		    sha1_to_hex(split_index->base->sha1));