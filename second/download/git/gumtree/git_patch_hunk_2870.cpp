 				if (value && !strcasecmp(value, "if-asked"))
 					set_push_cert_flags(flags, SEND_PACK_PUSH_CERT_IF_ASKED);
 				else
 					return error("Invalid value for '%s'", k);
 			}
 		}
+	} else if (!strcmp(k, "push.recursesubmodules")) {
+		const char *value;
+		if (!git_config_get_value("push.recursesubmodules", &value))
+			recurse_submodules = parse_push_recurse_submodules_arg(k, value);
 	}
 
 	return git_default_config(k, v, NULL);
 }
 
 int cmd_push(int argc, const char **argv, const char *prefix)
