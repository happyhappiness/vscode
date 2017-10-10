print_ref_status('!', "[remote rejected]", ref,
				 ref->deletion ? NULL : ref->peer_ref,
				 ref->remote_status, porcelain, summary_width);