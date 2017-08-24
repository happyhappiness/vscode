(iso9660->opt.joliet == OPT_JOLIET_LONGNAME)
			set_option_info(&info, &opt, "joliet",
			    KEY_STR, "long");
		else
			set_option_info(&info, &opt, "joliet",
			    KEY_FLG, iso9660->opt.joliet)