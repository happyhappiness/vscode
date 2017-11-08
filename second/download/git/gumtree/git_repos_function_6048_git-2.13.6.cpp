static int grep_cache(struct grep_opt *opt, const struct pathspec *pathspec,
		      int cached)
{
	int hit = 0;
	int nr;
	struct strbuf name = STRBUF_INIT;
	int name_base_len = 0;
	if (super_prefix) {
		name_base_len = strlen(super_prefix);
		strbuf_addstr(&name, super_prefix);
	}

	read_cache();

	for (nr = 0; nr < active_nr; nr++) {
		const struct cache_entry *ce = active_cache[nr];
		strbuf_setlen(&name, name_base_len);
		strbuf_addstr(&name, ce->name);

		if (S_ISREG(ce->ce_mode) &&
		    match_pathspec(pathspec, name.buf, name.len, 0, NULL,
				   S_ISDIR(ce->ce_mode) ||
				   S_ISGITLINK(ce->ce_mode))) {
			/*
			 * If CE_VALID is on, we assume worktree file and its
			 * cache entry are identical, even if worktree file has
			 * been modified, so use cache version instead
			 */
			if (cached || (ce->ce_flags & CE_VALID) ||
			    ce_skip_worktree(ce)) {
				if (ce_stage(ce) || ce_intent_to_add(ce))
					continue;
				hit |= grep_oid(opt, &ce->oid, ce->name,
						 0, ce->name);
			} else {
				hit |= grep_file(opt, ce->name);
			}
		} else if (recurse_submodules && S_ISGITLINK(ce->ce_mode) &&
			   submodule_path_match(pathspec, name.buf, NULL)) {
			hit |= grep_submodule(opt, NULL, ce->name, ce->name);
		} else {
			continue;
		}

		if (ce_stage(ce)) {
			do {
				nr++;
			} while (nr < active_nr &&
				 !strcmp(ce->name, active_cache[nr]->name));
			nr--; /* compensate for loop control */
		}
		if (hit && opt->status_only)
			break;
	}

	strbuf_release(&name);
	return hit;
}