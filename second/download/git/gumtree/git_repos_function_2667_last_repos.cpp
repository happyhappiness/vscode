int transport_push(struct transport *transport,
		   int refspec_nr, const char **refspec, int flags,
		   unsigned int *reject_reasons)
{
	*reject_reasons = 0;
	transport_verify_remote_names(refspec_nr, refspec);

	if (transport->push) {
		/* Maybe FIXME. But no important transport uses this case. */
		if (flags & TRANSPORT_PUSH_SET_UPSTREAM)
			die("This transport does not support using --set-upstream");

		return transport->push(transport, refspec_nr, refspec, flags);
	} else if (transport->push_refs) {
		struct ref *remote_refs;
		struct ref *local_refs = get_local_heads();
		int match_flags = MATCH_REFS_NONE;
		int verbose = (transport->verbose > 0);
		int quiet = (transport->verbose < 0);
		int porcelain = flags & TRANSPORT_PUSH_PORCELAIN;
		int pretend = flags & TRANSPORT_PUSH_DRY_RUN;
		int push_ret, ret, err;

		if (check_push_refs(local_refs, refspec_nr, refspec) < 0)
			return -1;

		remote_refs = transport->get_refs_list(transport, 1);

		if (flags & TRANSPORT_PUSH_ALL)
			match_flags |= MATCH_REFS_ALL;
		if (flags & TRANSPORT_PUSH_MIRROR)
			match_flags |= MATCH_REFS_MIRROR;
		if (flags & TRANSPORT_PUSH_PRUNE)
			match_flags |= MATCH_REFS_PRUNE;
		if (flags & TRANSPORT_PUSH_FOLLOW_TAGS)
			match_flags |= MATCH_REFS_FOLLOW_TAGS;

		if (match_push_refs(local_refs, &remote_refs,
				    refspec_nr, refspec, match_flags)) {
			return -1;
		}

		if (transport->smart_options &&
		    transport->smart_options->cas &&
		    !is_empty_cas(transport->smart_options->cas))
			apply_push_cas(transport->smart_options->cas,
				       transport->remote, remote_refs);

		set_ref_status_for_push(remote_refs,
			flags & TRANSPORT_PUSH_MIRROR,
			flags & TRANSPORT_PUSH_FORCE);

		if (!(flags & TRANSPORT_PUSH_NO_HOOK))
			if (run_pre_push_hook(transport, remote_refs))
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
		err = push_had_errors(remote_refs);
		ret = push_ret | err;

		if (!quiet || err)
			transport_print_push_status(transport->url, remote_refs,
					verbose | porcelain, porcelain,
					reject_reasons);

		if (flags & TRANSPORT_PUSH_SET_UPSTREAM)
			set_upstreams(transport, remote_refs, pretend);

		if (!(flags & (TRANSPORT_PUSH_DRY_RUN |
			       TRANSPORT_RECURSE_SUBMODULES_ONLY))) {
			struct ref *ref;
			for (ref = remote_refs; ref; ref = ref->next)
				transport_update_tracking_ref(transport->remote, ref, verbose);
		}

		if (porcelain && !push_ret)
			puts("Done");
		else if (!quiet && !ret && !transport_refs_pushed(remote_refs))
			fprintf(stderr, "Everything up-to-date\n");

		return ret;
	}
	return 1;
}