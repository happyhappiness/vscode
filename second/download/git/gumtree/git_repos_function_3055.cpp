static void drop_privileges(struct credentials *cred)
{
	if (cred && (initgroups(cred->pass->pw_name, cred->gid) ||
	    setgid (cred->gid) || setuid(cred->pass->pw_uid)))
		die("cannot drop privileges");
}