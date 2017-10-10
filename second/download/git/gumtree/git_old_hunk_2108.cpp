		break;
	case REF_STATUS_EXPECTING_REPORT:
		print_ref_status('!', "[remote failure]", ref,
						 ref->deletion ? NULL : ref->peer_ref,
						 "remote failed to report status", porcelain);
		break;
	case REF_STATUS_OK:
		print_ok_ref_status(ref, porcelain);
		break;
	}

	return 1;
