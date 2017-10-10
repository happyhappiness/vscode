	switch (count_refspec_match(dst_value, dst, &matched_dst)) {
	case 1:
		break;
	case 0:
		if (starts_with(dst_value, "refs/"))
			matched_dst = make_linked_ref(dst_value, dst_tail);
		else if (is_null_oid(&matched_src->new_oid))
			error("unable to delete '%s': remote ref does not exist",
			      dst_value);
		else if ((dst_guess = guess_ref(dst_value, matched_src)))
			matched_dst = make_linked_ref(dst_guess, dst_tail);
		else
			error("unable to push to unqualified destination: %s\n"
