static struct ref *wanted_peer_refs(const struct ref *refs,
		struct refspec *refspec)
{
	struct ref *head = copy_ref(find_ref_by_name(refs, "HEAD"));
	struct ref *local_refs = head;
	struct ref **tail = head ? &head->next : &local_refs;

	if (option_single_branch) {
		struct ref *remote_head = NULL;

		if (!option_branch)
			remote_head = guess_remote_head(head, refs, 0);
		else {
			local_refs = NULL;
			tail = &local_refs;
			remote_head = copy_ref(find_remote_branch(refs, option_branch));
		}

		if (!remote_head && option_branch)
			warning(_("Could not find remote branch %s to clone."),
				option_branch);
		else {
			get_fetch_map(remote_head, refspec, &tail, 0);

			/* if --branch=tag, pull the requested tag explicitly */
			get_fetch_map(remote_head, tag_refspec, &tail, 0);
		}
	} else
		get_fetch_map(refs, refspec, &tail, 0);

	if (!option_mirror && !option_single_branch)
		get_fetch_map(refs, tag_refspec, &tail, 0);

	return local_refs;
}