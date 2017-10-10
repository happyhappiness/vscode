	} else {
		finish_copy_notes_for_rewrite(c, msg);
	}
	return ret;
}

static struct notes_tree *init_notes_check(const char *subcommand)
{
	struct notes_tree *t;
	init_notes(NULL, NULL, NULL, 0);
	t = &default_notes_tree;

	if (!starts_with(t->ref, "refs/notes/"))
		die("Refusing to %s notes in %s (outside of refs/notes/)",
		    subcommand, t->ref);
	return t;
}

static int list(int argc, const char **argv, const char *prefix)
{
	struct notes_tree *t;
