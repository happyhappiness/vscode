
	if (type != FSCK_ERROR && msg_id_info[id].msg_type == FSCK_FATAL)
		die("Cannot demote %s to %s", msg_id, msg_type);

	if (!options->msg_type) {
		int i;
		int *msg_type = xmalloc(sizeof(int) * FSCK_MSG_MAX);
		for (i = 0; i < FSCK_MSG_MAX; i++)
			msg_type[i] = fsck_msg_type(i, options);
		options->msg_type = msg_type;
	}

	options->msg_type[id] = type;
