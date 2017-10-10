 		opt.cleanup_mode = CLEANUP_NONE;
 	else if (!strcmp(cleanup_arg, "whitespace"))
 		opt.cleanup_mode = CLEANUP_SPACE;
 	else
 		die(_("Invalid cleanup mode %s"), cleanup_arg);
 
-	if (annotate)
+	if (create_tag_object) {
+		if (force_sign_annotate && !annotate)
+			opt.sign = 1;
 		create_tag(object, tag, &buf, &opt, prev, object);
+	}
 
 	transaction = ref_transaction_begin(&err);
 	if (!transaction ||
 	    ref_transaction_update(transaction, ref.buf, object, prev,
 				   create_reflog ? REF_FORCE_CREATE_REFLOG : 0,
 				   NULL, &err) ||
