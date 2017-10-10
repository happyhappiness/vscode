			commit = get_merge_parent(merge_names->buf + pos);
			merge_names->buf[pos + 40] = saved;
		}
		if (!commit) {
			if (ptr)
				*ptr = '\0';
			die(_("not something we can merge in %s: %s"),
			    filename, merge_names->buf + pos);
		}
		remotes = &commit_list_insert(commit, remotes)->next;
	}

	if (merge_names == &fetch_head_file)
