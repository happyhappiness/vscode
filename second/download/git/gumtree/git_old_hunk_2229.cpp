			die(_("unable to handle file type %d"), (int)st.st_mode);

		if (rename(src, git_dir))
			die_errno(_("unable to move %s to %s"), src, git_dir);
	}

	fp = fopen(git_link, "w");
	if (!fp)
		die(_("Could not create git link %s"), git_link);
	fprintf(fp, "gitdir: %s\n", git_dir);
	fclose(fp);
}

int init_db(const char *template_dir, unsigned int flags)
{
	int reinit;
	const char *git_dir = get_git_dir();
