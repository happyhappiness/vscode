void *read_object_with_reference(const unsigned char *sha1,
				 const char *required_type_name,
				 unsigned long *size,
				 unsigned char *actual_sha1_return)
{
	enum object_type type, required_type;
	void *buffer;
	unsigned long isize;
	unsigned char actual_sha1[20];

	required_type = type_from_string(required_type_name);
	hashcpy(actual_sha1, sha1);
	while (1) {
		int ref_length = -1;
		const char *ref_type = NULL;

		buffer = read_sha1_file(actual_sha1, &type, &isize);
		if (!buffer)
			return NULL;
		if (type == required_type) {
			*size = isize;
			if (actual_sha1_return)
				hashcpy(actual_sha1_return, actual_sha1);
			return buffer;
		}
		/* Handle references */
		else if (type == OBJ_COMMIT)
			ref_type = "tree ";
		else if (type == OBJ_TAG)
			ref_type = "object ";
		else {
			free(buffer);
			return NULL;
		}
		ref_length = strlen(ref_type);

		if (ref_length + 40 > isize ||
		    memcmp(buffer, ref_type, ref_length) ||
		    get_sha1_hex((char *) buffer + ref_length, actual_sha1)) {
			free(buffer);
			return NULL;
		}
		free(buffer);
		/* Now we have the ID of the referred-to object in
		 * actual_sha1.  Check again. */
	}
}