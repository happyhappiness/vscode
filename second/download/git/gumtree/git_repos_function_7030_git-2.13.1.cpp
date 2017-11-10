static void gnome_keyring_done_cb(GnomeKeyringResult result, gpointer user_data)
{
	gpointer *data = (gpointer *)user_data;
	int *done = (int *)data[0];
	GnomeKeyringResult *r = (GnomeKeyringResult *)data[1];

	*r = result;
	*done = 1;
}