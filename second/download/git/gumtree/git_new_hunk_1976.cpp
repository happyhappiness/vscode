		write_merge_state(remoteheads);

	if (merge_was_ok)
		fprintf(stderr, _("Automatic merge went well; "
			"stopped before committing as requested\n"));
	else
		ret = suggest_conflicts();

done:
	free(branch_to_free);
	return ret;
}
