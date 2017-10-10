				die("Failed to push all needed submodules!");
			}
			sha1_array_clear(&commits);
		}

		if (((flags & TRANSPORT_RECURSE_SUBMODULES_CHECK) ||
		     ((flags & (TRANSPORT_RECURSE_SUBMODULES_ON_DEMAND |
				TRANSPORT_RECURSE_SUBMODULES_ONLY)) &&
		      !pretend)) && !is_bare_repository()) {
			struct ref *ref = remote_refs;
			struct string_list needs_pushing = STRING_LIST_INIT_DUP;
			struct sha1_array commits = SHA1_ARRAY_INIT;

			for (; ref; ref = ref->next)
