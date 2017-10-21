	}
	*bp = '\0';

	return bp - buf;
}

static int rsync_module(int f_in, int f_out, int i, char *addr, char *host)
{
	int argc;
	char **argv, **orig_argv, **orig_early_argv, *chroot_path = NULL;
	char line[BIGPATHBUFLEN];
	uid_t uid = (uid_t)-2;  /* canonically "nobody" */
	gid_t gid = (gid_t)-2;
	char *p, *err_msg = NULL;
	char *name = lp_name(i);
	int use_chroot = lp_use_chroot(i);
