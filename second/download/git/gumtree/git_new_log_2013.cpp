die("unable to generate diff (%s -> %s)",
		    sha1_to_hex(parent->commit->object.sha1),
		    sha1_to_hex(target->commit->object.sha1));