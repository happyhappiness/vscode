		o = parse_object(sha1_buf);
		if (!o)
			die("git upload-pack: not our ref %s",
			    sha1_to_hex(sha1_buf));
		if (!(o->flags & WANTED)) {
			o->flags |= WANTED;
			if (!((allow_unadvertised_object_request & ALLOW_ANY_SHA1) == ALLOW_ANY_SHA1
			      || is_our_ref(o)))
				has_non_tip = 1;
			add_object_array(o, NULL, &want_obj);
		}
	}

	/*
