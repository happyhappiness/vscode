			struct commit_list *base_list;
			struct commit *commit;
			struct object_id oid;

			if (get_oid(upstream, &oid))
				die(_("Failed to resolve '%s' as a valid ref."), upstream);
			commit = lookup_commit_or_die(oid.hash, "upstream base");
			base_list = get_merge_bases_many(commit, total, list);
			/* There should be one and only one merge base. */
			if (!base_list || base_list->next)
				die(_("Could not find exact merge base."));
			base = base_list->item;
			free_commit_list(base_list);
