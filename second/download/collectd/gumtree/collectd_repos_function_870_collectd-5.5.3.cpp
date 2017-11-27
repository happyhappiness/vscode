static int
check_permissions(void)
{
#ifdef HAVE_SYS_CAPABILITY_H
	struct __user_cap_header_struct cap_header_data;
	cap_user_header_t cap_header = &cap_header_data;
	struct __user_cap_data_struct cap_data_data;
	cap_user_data_t cap_data = &cap_data_data;
	int ret = 0;
#endif /* HAVE_SYS_CAPABILITY_H */

	if (getuid() == 0) {
		/* We have everything we need */
		return 0;
#ifndef HAVE_SYS_CAPABILITY_H
	} else {
		ERROR("turbostat plugin: Initialization failed: this plugin "
		      "requires collectd to run as root");
		return -1;
	}
#else /* HAVE_SYS_CAPABILITY_H */
	}