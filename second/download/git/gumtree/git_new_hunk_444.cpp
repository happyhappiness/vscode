
int check_ref_type(const struct ref *ref, int flags)
{
	return check_ref(ref->name, flags);
}

static void die_initial_contact(int unexpected)
{
	if (unexpected)
		die(_("The remote end hung up upon initial contact"));
	else
		die(_("Could not read from remote repository.\n\n"
		      "Please make sure you have the correct access rights\n"
		      "and the repository exists."));
}

static void parse_one_symref_info(struct string_list *symref, const char *val, int len)
{
	char *sym, *target;
	struct string_list_item *item;
