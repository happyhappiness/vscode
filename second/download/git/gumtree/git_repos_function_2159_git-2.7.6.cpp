int transport_refs_pushed(struct ref *ref)
{
	for (; ref; ref = ref->next) {
		switch(ref->status) {
		case REF_STATUS_NONE:
		case REF_STATUS_UPTODATE:
			break;
		default:
			return 1;
		}
	}
	return 0;
}