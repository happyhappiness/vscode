					      argc, argv, NULL);
		remote_head = remoteheads->item;
		if (!remote_head)
			die(_("%s - not something we can merge"), argv[0]);
		if (remoteheads->next)
			die(_("Can merge only exactly one commit into empty head"));
		read_empty(remote_head->object.sha1, 0);
		update_ref("initial pull", "HEAD", remote_head->object.sha1,
			   NULL, 0, UPDATE_REFS_DIE_ON_ERR);
		goto done;
	}

	/*
	 * This could be traditional "merge <msg> HEAD <commit>..."  and
