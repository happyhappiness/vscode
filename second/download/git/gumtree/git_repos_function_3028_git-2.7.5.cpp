static void make_service_overridable(const char *name, int ena)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(daemon_service); i++) {
		if (!strcmp(daemon_service[i].name, name)) {
			daemon_service[i].overridable = ena;
			return;
		}
	}
	die("No such service %s", name);
}