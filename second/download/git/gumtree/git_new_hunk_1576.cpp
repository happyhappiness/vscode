		return needs_pushing;
	}

	return 0;
}

int find_unpushed_submodules(struct oid_array *commits,
		const char *remotes_name, struct string_list *needs_pushing)
{
	struct string_list submodules = STRING_LIST_INIT_DUP;
	struct string_list_item *submodule;
	struct argv_array argv = ARGV_ARRAY_INIT;

	/* argv.argv[0] will be ignored by setup_revisions */
	argv_array_push(&argv, "find_unpushed_submodules");
	oid_array_for_each_unique(commits, append_oid_to_argv, &argv);
	argv_array_push(&argv, "--not");
	argv_array_pushf(&argv, "--remotes=%s", remotes_name);

	collect_changed_submodules(&submodules, &argv);

	for_each_string_list_item(submodule, &submodules) {
		struct oid_array *commits = submodule->util;
		const char *path = submodule->string;

		if (submodule_needs_pushing(path, commits))
			string_list_insert(needs_pushing, path);
	}

	free_submodules_oids(&submodules);
	argv_array_clear(&argv);

	return needs_pushing->nr;
}

static int push_submodule(const char *path,
			  const struct remote *remote,
