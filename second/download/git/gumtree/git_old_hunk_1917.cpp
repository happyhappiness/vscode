	if (type < 0)
		die("%s is not a valid object", sha1_to_hex(sha1));
	if (type != expect)
		die("%s is not a valid '%s' object", sha1_to_hex(sha1),
		    typename(expect));
}
