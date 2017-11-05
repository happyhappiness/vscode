static void verify_working_tree_path(struct commit *work_tree, const char *path)
{
	struct commit_list *parents;

	for (parents = work_tree->parents; parents; parents = parents->next) {
		const unsigned char *commit_sha1 = parents->item->object.sha1;
		unsigned char blob_sha1[20];
		unsigned mode;

		if (!get_tree_entry(commit_sha1, path, blob_sha1, &mode) &&
		    sha1_object_info(blob_sha1, NULL) == OBJ_BLOB)
			return;
	}
	die("no such path '%s' in HEAD", path);
}