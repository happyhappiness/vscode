static void check_non_tip(void)
{
	int i;

	/*
	 * In the normal in-process case without
	 * uploadpack.allowReachableSHA1InWant,
	 * non-tip requests can never happen.
	 */
	if (!stateless_rpc && !(allow_unadvertised_object_request & ALLOW_REACHABLE_SHA1))
		goto error;
	if (!has_unreachable(&want_obj))
		/* All the non-tip ones are ancestors of what we advertised */
		return;

error:
	/* Pick one of them (we know there at least is one) */
	for (i = 0; i < want_obj.nr; i++) {
		struct object *o = want_obj.objects[i].item;
		if (!is_our_ref(o))
			die("git upload-pack: not our ref %s",
			    oid_to_hex(&o->oid));
	}
}