				if (want_status == FETCH_HEAD_MERGE)
					warning(_("reject %s because shallow roots are not allowed to be updated"),
						rm->peer_ref ? rm->peer_ref->name : rm->name);
				continue;
			}

			commit = lookup_commit_reference_gently(rm->old_sha1, 1);
			if (!commit)
				rm->fetch_head_status = FETCH_HEAD_NOT_FOR_MERGE;

			if (rm->fetch_head_status != want_status)
				continue;

			if (rm->peer_ref) {
				ref = xcalloc(1, sizeof(*ref) + strlen(rm->peer_ref->name) + 1);
				strcpy(ref->name, rm->peer_ref->name);
				hashcpy(ref->old_sha1, rm->peer_ref->old_sha1);
				hashcpy(ref->new_sha1, rm->old_sha1);
				ref->force = rm->peer_ref->force;
			}


			if (!strcmp(rm->name, "HEAD")) {
				kind = "";
