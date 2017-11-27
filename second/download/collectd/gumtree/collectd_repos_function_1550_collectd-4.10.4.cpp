static int sensors_shutdown (void)
{
	sensors_free_features ();
	ignorelist_free (sensor_list);

	return (0);
}