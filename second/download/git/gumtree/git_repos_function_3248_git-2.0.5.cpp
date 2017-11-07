static void free_ref(struct ref *ref)
{
	if (!ref)
		return;
	free_ref(ref->peer_ref);
	free(ref->remote_status);
	free(ref->symref);
	free(ref);
}