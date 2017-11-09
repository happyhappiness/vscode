static int handle_dotdot(const char *arg,
			 struct rev_info *revs, int flags,
			 int cant_be_filename)
{
	struct object_context a_oc, b_oc;
	char *dotdot = strstr(arg, "..");
	int ret;

	if (!dotdot)
		return -1;

	memset(&a_oc, 0, sizeof(a_oc));
	memset(&b_oc, 0, sizeof(b_oc));

	*dotdot = '\0';
	ret = handle_dotdot_1(arg, dotdot, revs, flags, cant_be_filename,
			      &a_oc, &b_oc);
	*dotdot = '.';

	free(a_oc.path);
	free(b_oc.path);

	return ret;
}