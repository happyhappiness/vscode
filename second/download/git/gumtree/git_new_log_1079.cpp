die("broken index, expect %s in %s, got %s",
		    base_sha1_hex, base_path,
		    sha1_to_hex(split_index->base->sha1));