		if (!(flags & TRANSPORT_PUSH_NO_HOOK))
			if (run_pre_push_hook(transport, remote_refs))
				return -1;

		if ((flags & TRANSPORT_RECURSE_SUBMODULES_ON_DEMAND) && !is_bare_repository()) {
			struct ref *ref = remote_refs;
			for (; ref; ref = ref->next)
				if (!is_null_oid(&ref->new_oid) &&
				    !push_unpushed_submodules(ref->new_oid.hash,
					    transport->remote->name))
				    die ("Failed to push all needed submodules!");
		}

		if ((flags & (TRANSPORT_RECURSE_SUBMODULES_ON_DEMAND |
			      TRANSPORT_RECURSE_SUBMODULES_CHECK)) && !is_bare_repository()) {
			struct ref *ref = remote_refs;
			struct string_list needs_pushing = STRING_LIST_INIT_DUP;

			for (; ref; ref = ref->next)
				if (!is_null_oid(&ref->new_oid) &&
				    find_unpushed_submodules(ref->new_oid.hash,
					    transport->remote->name, &needs_pushing))
					die_with_unpushed_submodules(&needs_pushing);
		}

		push_ret = transport->push_refs(transport, remote_refs, flags);
		err = push_had_errors(remote_refs);
		ret = push_ret | err;

