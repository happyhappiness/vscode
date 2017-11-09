static void record_recent_commit(struct commit *commit, void *data)
{
	oid_array_append(&recent_objects, &commit->object.oid);
}