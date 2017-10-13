die("cannot simplify commit %s (because of %s)",
			    sha1_to_hex(commit->object.sha1),
			    sha1_to_hex(p->object.sha1));