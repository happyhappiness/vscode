error(_("binary patch to '%s' creates incorrect result (expecting %s, got %s)"),
				name, patch->new_sha1_prefix, sha1_to_hex(sha1));