	 * diff format and wishes to actually see all differences even if they
	 * haven't yet been committed to the submodule yet.
	 */
	if (!(dirty_submodule & DIRTY_SUBMODULE_MODIFIED))
		argv_array_push(&cp.args, oid_to_hex(new));

	prepare_submodule_repo_env(&cp.env_array);
	if (run_command(&cp))
		fprintf(f, "(diff failed)\n");

done:
	strbuf_release(&submodule_dir);
	if (merge_bases)
