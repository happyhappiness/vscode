static int append_ref_to_tracked_list(const char *refname,
	const unsigned char *sha1, int flags, void *cb_data)
{
	struct ref_states *states = cb_data;
	struct refspec refspec;

	if (flags & REF_ISSYMREF)
		return 0;

	memset(&refspec, 0, sizeof(refspec));
	refspec.dst = (char *)refname;
	if (!remote_find_tracking(states->remote, &refspec))
		string_list_append(&states->tracked, abbrev_branch(refspec.src));

	return 0;
}