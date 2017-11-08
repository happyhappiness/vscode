static void show_edge(struct commit *commit)
{
	add_preferred_base(commit->object.sha1);
}