static void *fill_tree_desc_strict(struct tree_desc *desc,
				   const unsigned char *hash)
{
	void *buffer;
	enum object_type type;
	unsigned long size;

	buffer = read_sha1_file(hash, &type, &size);
	if (!buffer)
		die("unable to read tree (%s)", sha1_to_hex(hash));
	if (type != OBJ_TREE)
		die("%s is not a tree", sha1_to_hex(hash));
	init_tree_desc(desc, buffer, size);
	return buffer;
}