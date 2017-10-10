					       "\n-----BEGIN PGP SIGNATURE-----\n");
		if (signature)
			switch(signed_tag_mode) {
			case ABORT:
				die ("Encountered signed tag %s; use "
				     "--signed-tags=<mode> to handle it.",
				     oid_to_hex(&tag->object.oid));
			case WARN:
				warning ("Exporting signed tag %s",
					 oid_to_hex(&tag->object.oid));
				/* fallthru */
			case VERBATIM:
				break;
			case WARN_STRIP:
				warning ("Stripping signature from tag %s",
					 oid_to_hex(&tag->object.oid));
				/* fallthru */
			case STRIP:
				message_size = signature + 1 - message;
				break;
			}
	}
