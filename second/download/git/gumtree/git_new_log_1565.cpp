strbuf_addf(err, "ref %s is at %s but expected %s",
			    lock->ref_name,
			    sha1_to_hex(lock->old_oid.hash),
			    sha1_to_hex(old_sha1));