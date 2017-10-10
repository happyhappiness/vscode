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
