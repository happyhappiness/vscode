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
			      "The destination refspec neither matches an "
			      "existing ref on the remote nor\n"
			      "begins with refs/, and we are unable to "
			      "guess a prefix based on the source ref.",
			      dst_value);
