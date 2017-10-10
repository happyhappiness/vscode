				die("Failed to find/parse commit %s", t->ref);
			commit_list_insert(parent, &parents);
		}
		/* else: t->ref points to nothing, assume root/orphan commit */
	}

	if (commit_tree(msg, tree_sha1, parents, result_sha1, NULL, NULL))
		die("Failed to commit notes tree to database");
}

void commit_notes(struct notes_tree *t, const char *msg)
{
	struct strbuf buf = STRBUF_INIT;
