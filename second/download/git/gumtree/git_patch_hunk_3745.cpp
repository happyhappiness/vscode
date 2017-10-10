 		strbuf_reset(&var);
 	}
 
 	strbuf_release(&var);
 }
 
-static struct rpc_service *select_service(const char *name)
+static struct rpc_service *select_service(struct strbuf *hdr, const char *name)
 {
 	const char *svc_name;
 	struct rpc_service *svc = NULL;
 	int i;
 
 	if (!skip_prefix(name, "git-", &svc_name))
-		forbidden("Unsupported service: '%s'", name);
+		forbidden(hdr, "Unsupported service: '%s'", name);
 
 	for (i = 0; i < ARRAY_SIZE(rpc_service); i++) {
 		struct rpc_service *s = &rpc_service[i];
 		if (!strcmp(s->name, svc_name)) {
 			svc = s;
 			break;
 		}
 	}
 
 	if (!svc)
-		forbidden("Unsupported service: '%s'", name);
+		forbidden(hdr, "Unsupported service: '%s'", name);
 
 	if (svc->enabled < 0) {
 		const char *user = getenv("REMOTE_USER");
 		svc->enabled = (user && *user) ? 1 : 0;
 	}
 	if (!svc->enabled)
-		forbidden("Service not enabled: '%s'", svc->name);
+		forbidden(hdr, "Service not enabled: '%s'", svc->name);
 	return svc;
 }
 
 /*
  * This is basically strbuf_read(), except that if we
  * hit max_request_buffer we die (we'd rather reject a
