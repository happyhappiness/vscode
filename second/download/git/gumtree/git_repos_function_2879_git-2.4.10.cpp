static struct credentials *prepare_credentials(const char *user_name,
    const char *group_name)
{
	static struct credentials c;

	c.pass = getpwnam(user_name);
	if (!c.pass)
		die("user not found - %s", user_name);

	if (!group_name)
		c.gid = c.pass->pw_gid;
	else {
		struct group *group = getgrnam(group_name);
		if (!group)
			die("group not found - %s", group_name);

		c.gid = group->gr_gid;
	}

	return &c;
}