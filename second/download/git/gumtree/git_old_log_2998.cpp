die("Invalid commit %s in submodule path %s%s",
				    sha1_to_hex(entry.sha1),
				    base->buf, entry.path);