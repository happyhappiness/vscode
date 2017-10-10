print_ref_status('!', "[remote failure]", ref,
						 ref->deletion ? NULL : ref->peer_ref,
						 "remote failed to report status", porcelain);