static const char commit_tree_usage[] = "git commit-tree [(-p <sha1>)...] [-S[<keyid>]] [-m <message>] [-F <file>] <sha1>";

static const char *sign_commit;

static void new_parent(struct commit *parent, struct commit_list **parents_p)
{
	unsigned char *sha1 = parent->object.sha1;
	struct commit_list *parents;
	for (parents = *parents_p; parents; parents = parents->next) {
		if (parents->item == parent) {
			error("duplicate parent %s ignored", sha1_to_hex(sha1));
			return;
		}
		parents_p = &parents->next;
	}
	commit_list_insert(parent, parents_p);
}
