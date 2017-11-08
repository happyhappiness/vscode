void assert_sha1_type(const unsigned char *sha1, enum object_type expect)
{
	enum object_type type = sha1_object_info(sha1, NULL);
	if (type < 0)
		die("%s is not a valid object", sha1_to_hex(sha1));
	if (type != expect)
		die("%s is not a valid '%s' object", sha1_to_hex(sha1),
		    typename(expect));
}