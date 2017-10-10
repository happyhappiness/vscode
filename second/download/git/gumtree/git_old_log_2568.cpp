printf("Merging remote commit %.7s into local commit %.7s with "
			"merge-base %.7s\n", sha1_to_hex(remote->object.sha1),
			sha1_to_hex(local->object.sha1),
			sha1_to_hex(base_sha1));