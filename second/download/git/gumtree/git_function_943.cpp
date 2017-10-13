int report_unmatched_refs(struct ref **sought, int nr_sought)
{
	int i, ret = 0;

	for (i = 0; i < nr_sought; i++) {
		if (!sought[i])
			continue;
		switch (sought[i]->match_status) {
		case REF_MATCHED:
			continue;
		case REF_NOT_MATCHED:
			error(_("no such remote ref %s"), sought[i]->name);
			break;
		case REF_UNADVERTISED_NOT_ALLOWED:
			error(_("Server does not allow request for unadvertised object %s"),
			      sought[i]->name);
			break;
		}
		ret = 1;
	}
	return ret;
}