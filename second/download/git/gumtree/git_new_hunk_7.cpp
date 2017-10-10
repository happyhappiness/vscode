						"pack/tmp_pack_XXXXXX");
			pack_name = xstrdup(tmp_file);
		} else
			output_fd = open(pack_name, O_CREAT|O_EXCL|O_RDWR, 0600);
		if (output_fd < 0)
			die_errno(_("unable to create '%s'"), pack_name);
		nothread_data.pack_fd = output_fd;
	} else {
		input_fd = open(pack_name, O_RDONLY);
		if (input_fd < 0)
			die_errno(_("cannot open packfile '%s'"), pack_name);
		output_fd = -1;
		nothread_data.pack_fd = input_fd;
	}
	git_SHA1_Init(&input_ctx);
	return pack_name;
}

static void parse_pack_header(void)
