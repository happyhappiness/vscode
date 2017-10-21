	if (!file->basename) out_of_memory("receive_file_entry 1");


	file->flags = flags;
	file->length = read_longint(f);
	file->modtime = (flags & SAME_TIME) ? last_time : (time_t)read_int(f);
	file->mode = (flags & SAME_MODE) ? last_mode : (mode_t)read_int(f);
	if (preserve_uid)
		file->uid = (flags & SAME_UID) ? last_uid : (uid_t)read_int(f);
	if (preserve_gid)
		file->gid = (flags & SAME_GID) ? last_gid : (gid_t)read_int(f);
	if (preserve_devices && IS_DEVICE(file->mode))
		file->rdev = (flags & SAME_RDEV) ? last_rdev : (dev_t)read_int(f);
