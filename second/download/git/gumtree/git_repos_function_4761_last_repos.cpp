const char *default_notes_ref(void)
{
	const char *notes_ref = NULL;
	if (!notes_ref)
		notes_ref = getenv(GIT_NOTES_REF_ENVIRONMENT);
	if (!notes_ref)
		notes_ref = notes_ref_name; /* value of core.notesRef config */
	if (!notes_ref)
		notes_ref = GIT_NOTES_DEFAULT_REF;
	return notes_ref;
}