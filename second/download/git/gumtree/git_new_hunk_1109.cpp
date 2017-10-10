				return -1;

		if ((flags & (TRANSPORT_RECURSE_SUBMODULES_ON_DEMAND |
			      TRANSPORT_RECURSE_SUBMODULES_ONLY)) &&
		    !is_bare_repository()) {
			struct ref *ref = remote_refs;
			struct oid_array commits = OID_ARRAY_INIT;

			for (; ref; ref = ref->next)
				if (!is_null_oid(&ref->new_oid))
					oid_array_append(&commits,
							  &ref->new_oid);

			if (!push_unpushed_submodules(&commits,
						      transport->remote,
						      refspec, refspec_nr,
						      transport->push_options,
						      pretend)) {
				oid_array_clear(&commits);
				die("Failed to push all needed submodules!");
			}
			oid_array_clear(&commits);
		}

		if (((flags & TRANSPORT_RECURSE_SUBMODULES_CHECK) ||
		     ((flags & (TRANSPORT_RECURSE_SUBMODULES_ON_DEMAND |
				TRANSPORT_RECURSE_SUBMODULES_ONLY)) &&
		      !pretend)) && !is_bare_repository()) {
			struct ref *ref = remote_refs;
			struct string_list needs_pushing = STRING_LIST_INIT_DUP;
			struct oid_array commits = OID_ARRAY_INIT;

			for (; ref; ref = ref->next)
				if (!is_null_oid(&ref->new_oid))
					oid_array_append(&commits,
							  &ref->new_oid);

			if (find_unpushed_submodules(&commits, transport->remote->name,
						&needs_pushing)) {
				oid_array_clear(&commits);
				die_with_unpushed_submodules(&needs_pushing);
			}
			string_list_clear(&needs_pushing, 0);
			oid_array_clear(&commits);
		}

		if (!(flags & TRANSPORT_RECURSE_SUBMODULES_ONLY))
			push_ret = transport->push_refs(transport, remote_refs, flags);
		else
			push_ret = 0;
