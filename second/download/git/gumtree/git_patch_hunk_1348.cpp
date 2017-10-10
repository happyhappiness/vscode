 	 */
 	cb_data.remote = remote;
 	result = for_each_ref(add_branch_for_removal, &cb_data);
 	strbuf_release(&buf);
 
 	if (!result)
-		result = delete_refs(&branches, REF_NODEREF);
+		result = delete_refs("remote: remove", &branches, REF_NODEREF);
 	string_list_clear(&branches, 0);
 
 	if (skipped.nr) {
 		fprintf_ln(stderr,
 			   Q_("Note: A branch outside the refs/remotes/ hierarchy was not removed;\n"
 			      "to delete it, use:",
