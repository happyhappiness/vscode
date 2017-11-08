static GnomeKeyringResult gnome_keyring_item_delete_sync(const char *keyring, guint32 id)
{
	int done = 0;
	GnomeKeyringResult result;
	gpointer data[] = { &done, &result };

	gnome_keyring_item_delete(keyring, id, gnome_keyring_done_cb, data,
		NULL);

	wait_for_request_completion(&done);

	return result;
}