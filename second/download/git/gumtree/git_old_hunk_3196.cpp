static enum protocol get_protocol(const char *name)
{
	if (!strcmp(name, "ssh"))
		return PROTO_SSH;
	if (!strcmp(name, "git"))
		return PROTO_GIT;
	if (!strcmp(name, "git+ssh"))
		return PROTO_SSH;
	if (!strcmp(name, "ssh+git"))
		return PROTO_SSH;
	if (!strcmp(name, "file"))
		return PROTO_FILE;
	die("I don't handle protocol '%s'", name);
}

