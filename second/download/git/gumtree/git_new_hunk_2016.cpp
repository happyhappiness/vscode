			die("More than one commit to dig from %s and %s?",
			    revs->pending.objects[i].name,
			    final_commit_name);
		sb->final = (struct commit *) obj;
		final_commit_name = revs->pending.objects[i].name;
	}
	return xstrdup_or_null(final_commit_name);
}

static char *prepare_initial(struct scoreboard *sb)
{
	int i;
	const char *final_commit_name = NULL;
	struct rev_info *revs = sb->revs;

	/*
