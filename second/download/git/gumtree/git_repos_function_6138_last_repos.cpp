static int grep_tree(struct grep_opt *opt, const struct pathspec *pathspec,
		     struct tree_desc *tree, struct strbuf *base, int tn_len,
		     int check_attr)
{
	int hit = 0;
	enum interesting match = entry_not_interesting;
	struct name_entry entry;
	int old_baselen = base->len;
	struct strbuf name = STRBUF_INIT;
	int name_base_len = 0;
	if (super_prefix) {
		strbuf_addstr(&name, super_prefix);
		name_base_len = name.len;
	}

	while (tree_entry(tree, &entry)) {
		int te_len = tree_entry_len(&entry);

		if (match != all_entries_interesting) {
			strbuf_addstr(&name, base->buf + tn_len);
			match = tree_entry_interesting(&entry, &name,
						       0, pathspec);
			strbuf_setlen(&name, name_base_len);

			if (match == all_entries_not_interesting)
				break;
			if (match == entry_not_interesting)
				continue;
		}

		strbuf_add(base, entry.path, te_len);

		if (S_ISREG(entry.mode)) {
			hit |= grep_oid(opt, entry.oid, base->buf, tn_len,
					 check_attr ? base->buf + tn_len : NULL);
		} else if (S_ISDIR(entry.mode)) {
			enum object_type type;
			struct tree_desc sub;
			void *data;
			unsigned long size;

			data = lock_and_read_oid_file(entry.oid, &type, &size);
			if (!data)
				die(_("unable to read tree (%s)"),
				    oid_to_hex(entry.oid));

			strbuf_addch(base, '/');
			init_tree_desc(&sub, data, size);
			hit |= grep_tree(opt, pathspec, &sub, base, tn_len,
					 check_attr);
			free(data);
		} else if (recurse_submodules && S_ISGITLINK(entry.mode)) {
			hit |= grep_submodule(opt, entry.oid, base->buf,
					      base->buf + tn_len);
		}

		strbuf_setlen(base, old_baselen);

		if (hit && opt->status_only)
			break;
	}

	strbuf_release(&name);
	return hit;
}