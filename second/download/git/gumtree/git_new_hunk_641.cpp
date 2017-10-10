		if (!(flags & TRANSPORT_PUSH_NO_HOOK))
			if (run_pre_push_hook(transport, remote_refs))
				return -1;

		if ((flags & TRANSPORT_RECURSE_SUBMODULES_ON_DEMAND) && !is_bare_repository()) {
			struct ref *ref = remote_refs;
			struct sha1_array commits = SHA1_ARRAY_INIT;

			for (; ref; ref = ref->next)
				if (!is_null_oid(&ref->new_oid))
					sha1_array_append(&commits, ref->new_oid.hash);

			if (!push_unpushed_submodules(&commits,
						      transport->remote->name,
						      pretend)) {
				sha1_array_clear(&commits);
				die("Failed to push all needed submodules!");
			}
			sha1_array_clear(&commits);
		}

		if (((flags & TRANSPORT_RECURSE_SUBMODULES_CHECK) ||
		     ((flags & TRANSPORT_RECURSE_SUBMODULES_ON_DEMAND) &&
		      !pretend)) && !is_bare_repository()) {
			struct ref *ref = remote_refs;
			struct string_list needs_pushing = STRING_LIST_INIT_DUP;
			struct sha1_array commits = SHA1_ARRAY_INIT;

			for (; ref; ref = ref->next)
				if (!is_null_oid(&ref->new_oid))
					sha1_array_append(&commits, ref->new_oid.hash);

			if (find_unpushed_submodules(&commits, transport->remote->name,
						&needs_pushing)) {
				sha1_array_clear(&commits);
				die_with_unpushed_submodules(&needs_pushing);
			}
			string_list_clear(&needs_pushing, 0);
			sha1_array_clear(&commits);
		}

		push_ret = transport->push_refs(transport, remote_refs, flags);
		err = push_had_errors(remote_refs);
		ret = push_ret | err;

