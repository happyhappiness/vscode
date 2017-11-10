static int run_service(const char *dir, struct daemon_service *service)
{
	const char *path;
	int enabled = service->enabled;
	struct strbuf var = STRBUF_INIT;

	loginfo("Request %s for '%s'", service->name, dir);

	if (!enabled && !service->overridable) {
		logerror("'%s': service not enabled.", service->name);
		errno = EACCES;
		return daemon_error(dir, "service not enabled");
	}

	if (!(path = path_ok(dir)))
		return daemon_error(dir, "no such repository");

	/*
	 * Security on the cheap.
	 *
	 * We want a readable HEAD, usable "objects" directory, and
	 * a "git-daemon-export-ok" flag that says that the other side
	 * is ok with us doing this.
	 *
	 * path_ok() uses enter_repo() and does whitelist checking.
	 * We only need to make sure the repository is exported.
	 */

	if (!export_all_trees && access("git-daemon-export-ok", F_OK)) {
		logerror("'%s': repository not exported.", path);
		errno = EACCES;
		return daemon_error(dir, "repository not exported");
	}

	if (service->overridable) {
		strbuf_addf(&var, "daemon.%s", service->config_name);
		git_config_get_bool(var.buf, &enabled);
		strbuf_release(&var);
	}
	if (!enabled) {
		logerror("'%s': service not enabled for '%s'",
			 service->name, path);
		errno = EACCES;
		return daemon_error(dir, "service not enabled");
	}

	/*
	 * Optionally, a hook can choose to deny access to the
	 * repository depending on the phase of the moon.
	 */
	if (access_hook && run_access_hook(service, dir, path))
		return -1;

	/*
	 * We'll ignore SIGTERM from now on, we have a
	 * good client.
	 */
	signal(SIGTERM, SIG_IGN);

	return service->fn();
}