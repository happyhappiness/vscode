
	shallow_nr += shallows.nr;
	free(shallows.objects);
}

/* return non-zero if the ref is hidden, otherwise 0 */
static int mark_our_ref(const char *refname, const unsigned char *sha1)
{
	struct object *o = lookup_unknown_object(sha1);

	if (ref_is_hidden(refname)) {
		o->flags |= HIDDEN_REF;
		return 1;
	}
	o->flags |= OUR_REF;
	return 0;
}

static int check_ref(const char *refname, const unsigned char *sha1, int flag, void *cb_data)
{
	mark_our_ref(refname, sha1);
	return 0;
}

static void format_symref_info(struct strbuf *buf, struct string_list *symref)
{
	struct string_list_item *item;

	if (!symref->nr)
		return;
