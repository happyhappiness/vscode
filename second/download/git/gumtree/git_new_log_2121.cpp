argv_array_pushl(&cp.args, "update-ref", "HEAD",
				 sha1_to_hex(commit->object.sha1), NULL);