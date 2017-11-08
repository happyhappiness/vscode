static int patch_id_defined(struct commit *commit)
{
	/* must be 0 or 1 parents */
	return !commit->parents || !commit->parents->next;
}