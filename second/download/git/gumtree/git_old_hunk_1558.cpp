		      "Stopping at filesystem boundary (GIT_DISCOVERY_ACROSS_FILESYSTEM not set)."),
		    dir.buf);
	default:
		die("BUG: unhandled setup_git_directory_1() result");
	}

	env_prefix = getenv(GIT_TOPLEVEL_PREFIX_ENVIRONMENT);
	if (env_prefix)
		prefix = env_prefix;

	if (prefix)
		setenv(GIT_PREFIX_ENVIRONMENT, prefix, 1);
	else
		setenv(GIT_PREFIX_ENVIRONMENT, "", 1);

	startup_info->have_repository = !nongit_ok || !*nongit_ok;
	startup_info->prefix = prefix;

	strbuf_release(&dir);
	strbuf_release(&gitdir);

	return prefix;
}

