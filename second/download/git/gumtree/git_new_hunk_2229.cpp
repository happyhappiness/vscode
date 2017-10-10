			die(_("unable to handle file type %d"), (int)st.st_mode);

		if (rename(src, git_dir))
			die_errno(_("unable to move %s to %s"), src, git_dir);
	}

	write_file(git_link, 1, "gitdir: %s\n", git_dir);
}

int init_db(const char *template_dir, unsigned int flags)
{
	int reinit;
	const char *git_dir = get_git_dir();
