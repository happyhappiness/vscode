			if (linelen != 48)
				die("bad parent line in commit");
			continue;
		}

		if (!parents_shown) {
			unsigned num = commit_list_count(commit->parents);
			/* with enough slop */
			strbuf_grow(sb, num * 50 + 20);
			add_merge_info(pp, sb, commit);
			parents_shown = 1;
		}

