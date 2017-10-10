
		if (!pretend)
			install_branch_config(BRANCH_CONFIG_VERBOSE,
				localname + 11, transport->remote->name,
				remotename);
		else
			printf(_("Would set upstream of '%s' to '%s' of '%s'\n"),
				localname + 11, remotename + 11,
				transport->remote->name);
	}
}

struct bundle_transport_data {
