					       "\n-----BEGIN PGP SIGNATURE-----\n");
		if (signature)
			switch(signed_tag_mode) {
			case ABORT:
				die ("Encountered signed tag %s; use "
				     "--signed-tags=<mode> to handle it.",
				     sha1_to_hex(tag->object.sha1));
			case WARN:
				warning ("Exporting signed tag %s",
					 sha1_to_hex(tag->object.sha1));
				/* fallthru */
			case VERBATIM:
				break;
			case WARN_STRIP:
				warning ("Stripping signature from tag %s",
					 sha1_to_hex(tag->object.sha1));
				/* fallthru */
			case STRIP:
				message_size = signature + 1 - message;
				break;
			}
	}
