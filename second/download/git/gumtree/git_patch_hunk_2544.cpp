 	if (!strcmp(k, "push.followtags")) {
 		if (git_config_bool(k, v))
 			*flags |= TRANSPORT_PUSH_FOLLOW_TAGS;
 		else
 			*flags &= ~TRANSPORT_PUSH_FOLLOW_TAGS;
 		return 0;
+	} else if (!strcmp(k, "push.gpgsign")) {
+		const char *value;
+		if (!git_config_get_value("push.gpgsign", &value)) {
+			switch (git_config_maybe_bool("push.gpgsign", value)) {
+			case 0:
+				set_push_cert_flags(flags, SEND_PACK_PUSH_CERT_NEVER);
+				break;
+			case 1:
+				set_push_cert_flags(flags, SEND_PACK_PUSH_CERT_ALWAYS);
+				break;
+			default:
+				if (value && !strcasecmp(value, "if-asked"))
+					set_push_cert_flags(flags, SEND_PACK_PUSH_CERT_IF_ASKED);
+				else
+					return error("Invalid value for '%s'", k);
+			}
+		}
 	}
 
 	return git_default_config(k, v, NULL);
 }
 
 int cmd_push(int argc, const char **argv, const char *prefix)
 {
 	int flags = 0;
 	int tags = 0;
+	int push_cert = -1;
 	int rc;
 	const char *repo = NULL;	/* default repository */
 	struct option options[] = {
 		OPT__VERBOSITY(&verbosity),
 		OPT_STRING( 0 , "repo", &repo, N_("repository"), N_("repository")),
 		OPT_BIT( 0 , "all", &flags, N_("push all refs"), TRANSPORT_PUSH_ALL),
