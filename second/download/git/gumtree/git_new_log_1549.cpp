die((flags & HASH_WRITE_OBJECT)
		    ? "Unable to add %s to database"
		    : "Unable to hash %s", path);