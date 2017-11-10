static void record_person(int which, struct string_list *people,
			  struct commit *commit)
{
	const char *buffer = get_commit_buffer(commit, NULL);
	record_person_from_buf(which, people, buffer);
	unuse_commit_buffer(commit, buffer);
}