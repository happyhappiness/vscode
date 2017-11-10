static int push_with_options(struct transport *transport, int flags)
{
	int err;
	unsigned int reject_reasons;

	transport_set_verbosity(transport, verbosity, progress);
	transport->family = family;

	if (receivepack)
		transport_set_option(transport,
				     TRANS_OPT_RECEIVEPACK, receivepack);
	transport_set_option(transport, TRANS_OPT_THIN, thin ? "yes" : NULL);

	if (!is_empty_cas(&cas)) {
		if (!transport->smart_options)
			die("underlying transport does not support --%s option",
			    CAS_OPT_NAME);
		transport->smart_options->cas = &cas;
	}

	if (verbosity > 0)
		fprintf(stderr, _("Pushing to %s\n"), transport->url);
	err = transport_push(transport, refspec_nr, refspec, flags,
			     &reject_reasons);
	if (err != 0)
		error(_("failed to push some refs to '%s'"), transport->url);

	err |= transport_disconnect(transport);
	if (!err)
		return 0;

	if (reject_reasons & REJECT_NON_FF_HEAD) {
		advise_pull_before_push();
	} else if (reject_reasons & REJECT_NON_FF_OTHER) {
		advise_checkout_pull_push();
	} else if (reject_reasons & REJECT_ALREADY_EXISTS) {
		advise_ref_already_exists();
	} else if (reject_reasons & REJECT_FETCH_FIRST) {
		advise_ref_fetch_first();
	} else if (reject_reasons & REJECT_NEEDS_FORCE) {
		advise_ref_needs_force();
	}

	return 1;
}