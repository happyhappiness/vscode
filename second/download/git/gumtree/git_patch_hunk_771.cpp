 		if (set_helper_option(transport, TRANS_OPT_PUSH_CERT, "true") != 0)
 			die("helper %s does not support --signed", name);
 	} else if (flags & TRANSPORT_PUSH_CERT_IF_ASKED) {
 		if (set_helper_option(transport, TRANS_OPT_PUSH_CERT, "if-asked") != 0)
 			die("helper %s does not support --signed=if-asked", name);
 	}
+
+	if (flags & TRANSPORT_PUSH_OPTIONS) {
+		struct string_list_item *item;
+		for_each_string_list_item(item, transport->push_options)
+			if (set_helper_option(transport, "push-option", item->string) != 0)
+				die("helper %s does not support 'push-option'", name);
+	}
 }
 
 static int push_refs_with_push(struct transport *transport,
 			       struct ref *remote_refs, int flags)
 {
 	int force_all = flags & TRANSPORT_PUSH_FORCE;
