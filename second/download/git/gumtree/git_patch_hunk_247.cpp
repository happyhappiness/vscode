 				    die ("Failed to push all needed submodules!");
 		}
 
 		if ((flags & (TRANSPORT_RECURSE_SUBMODULES_ON_DEMAND |
 			      TRANSPORT_RECURSE_SUBMODULES_CHECK)) && !is_bare_repository()) {
 			struct ref *ref = remote_refs;
-			struct string_list needs_pushing;
+			struct string_list needs_pushing = STRING_LIST_INIT_DUP;
 
-			memset(&needs_pushing, 0, sizeof(struct string_list));
-			needs_pushing.strdup_strings = 1;
 			for (; ref; ref = ref->next)
 				if (!is_null_sha1(ref->new_sha1) &&
 				    find_unpushed_submodules(ref->new_sha1,
 					    transport->remote->name, &needs_pushing))
 					die_with_unpushed_submodules(&needs_pushing);
 		}
