		snprintf(name, sizeof(name), "%s/pack/pack-%s.keep",
			 get_object_directory(), sha1_to_hex(p->sha1));
		unlink_or_warn(name);
	}
}

static void end_packfile(void)
{
	static int running;

	if (running || !pack_data)
		return;
