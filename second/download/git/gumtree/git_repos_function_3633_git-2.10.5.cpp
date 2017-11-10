static int splice_tree(const unsigned char *hash1,
		       const char *prefix,
		       const unsigned char *hash2,
		       unsigned char *result)
{
	char *subpath;
	int toplen;
	char *buf;
	unsigned long sz;
	struct tree_desc desc;
	unsigned char *rewrite_here;
	const unsigned char *rewrite_with;
	unsigned char subtree[20];
	enum object_type type;
	int status;

	subpath = strchrnul(prefix, '/');
	toplen = subpath - prefix;
	if (*subpath)
		subpath++;

	buf = read_sha1_file(hash1, &type, &sz);
	if (!buf)
		die("cannot read tree %s", sha1_to_hex(hash1));
	init_tree_desc(&desc, buf, sz);

	rewrite_here = NULL;
	while (desc.size) {
		const char *name;
		unsigned mode;
		const struct object_id *oid;

		oid = tree_entry_extract(&desc, &name, &mode);
		if (strlen(name) == toplen &&
		    !memcmp(name, prefix, toplen)) {
			if (!S_ISDIR(mode))
				die("entry %s in tree %s is not a tree",
				    name, sha1_to_hex(hash1));
			rewrite_here = (unsigned char *) oid->hash;
			break;
		}
		update_tree_entry(&desc);
	}
	if (!rewrite_here)
		die("entry %.*s not found in tree %s",
		    toplen, prefix, sha1_to_hex(hash1));
	if (*subpath) {
		status = splice_tree(rewrite_here, subpath, hash2, subtree);
		if (status)
			return status;
		rewrite_with = subtree;
	}
	else
		rewrite_with = hash2;
	hashcpy(rewrite_here, rewrite_with);
	status = write_sha1_file(buf, sz, tree_type, result);
	free(buf);
	return status;
}