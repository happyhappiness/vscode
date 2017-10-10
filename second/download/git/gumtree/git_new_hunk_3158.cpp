	} else {
		finish_copy_notes_for_rewrite(c, msg);
	}
	return ret;
}

static struct notes_tree *init_notes_check(const char *subcommand,
					   int flags)
{
	struct notes_tree *t;
	const char *ref;
	init_notes(NULL, NULL, NULL, flags);
	t = &default_notes_tree;

	ref = (flags & NOTES_INIT_WRITABLE) ? t->update_ref : t->ref;
	if (!starts_with(ref, "refs/notes/"))
		die("Refusing to %s notes in %s (outside of refs/notes/)",
		    subcommand, ref);
	return t;
}

static int list(int argc, const char **argv, const char *prefix)
{
	struct notes_tree *t;
