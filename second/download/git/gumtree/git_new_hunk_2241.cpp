	cb_data.remote = remote;
	result = for_each_ref(add_branch_for_removal, &cb_data);
	strbuf_release(&buf);

	if (!result)
		result = remove_branches(&branches);
	string_list_clear(&branches, 0);

	if (skipped.nr) {
		fprintf_ln(stderr,
			   Q_("Note: A branch outside the refs/remotes/ hierarchy was not removed;\n"
			      "to delete it, use:",
			      "Note: Some branches outside the refs/remotes/ hierarchy were not removed;\n"
