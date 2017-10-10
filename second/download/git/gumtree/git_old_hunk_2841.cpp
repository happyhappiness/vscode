				    && (!cover_letter || rev.nr > 1))
					free(rev.message_id);
				else
					string_list_append(rev.ref_message_ids,
							   rev.message_id);
			}
			gen_message_id(&rev, sha1_to_hex(commit->object.sha1));
		}

		if (!use_stdout &&
		    reopen_stdout(rev.numbered_files ? NULL : commit, NULL, &rev, quiet))
			die(_("Failed to create output files"));
		shown = log_tree_commit(&rev, commit);
