 	set_helper_option(t, "progress", t->progress ? "true" : "false");
 
 	n = snprintf(buf, sizeof(buf), "%d", v + 1);
 	if (n >= sizeof(buf))
 		die("impossibly large verbosity value");
 	set_helper_option(t, "verbosity", buf);
+
+	switch (t->family) {
+	case TRANSPORT_FAMILY_ALL:
+		/*
+		 * this is already the default,
+		 * do not break old remote helpers by setting "all" here
+		 */
+		break;
+	case TRANSPORT_FAMILY_IPV4:
+		set_helper_option(t, "family", "ipv4");
+		break;
+	case TRANSPORT_FAMILY_IPV6:
+		set_helper_option(t, "family", "ipv6");
+		break;
+	}
 }
 
 static int release_helper(struct transport *transport)
 {
 	int res = 0;
 	struct helper_data *data = transport->data;
