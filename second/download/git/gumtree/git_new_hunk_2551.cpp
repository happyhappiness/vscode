		if (create_symref(buf.buf, buf2.buf, buf3.buf))
			die(_("creating '%s' failed"), buf.buf);
	}
	return 0;
}

static int rm(int argc, const char **argv)
{
	struct option options[] = {
		OPT_END()
	};
	struct remote *remote;
