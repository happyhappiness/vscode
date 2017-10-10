 		logerror("'%s': repository not exported.", path);
 		errno = EACCES;
 		return daemon_error(dir, "repository not exported");
 	}
 
 	if (service->overridable) {
-		service_looking_at = service;
-		service_enabled = -1;
-		git_config(git_daemon_config, NULL);
-		if (0 <= service_enabled)
-			enabled = service_enabled;
+		strbuf_addf(&var, "daemon.%s", service->config_name);
+		git_config_get_bool(var.buf, &enabled);
+		strbuf_release(&var);
 	}
 	if (!enabled) {
 		logerror("'%s': service not enabled for '%s'",
 			 service->name, path);
 		errno = EACCES;
 		return daemon_error(dir, "service not enabled");
