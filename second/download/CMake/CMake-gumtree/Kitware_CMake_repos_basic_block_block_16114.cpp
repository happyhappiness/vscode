(iso9660->opt.rr == OPT_RR_DISABLED)
			set_option_info(&info, &opt, "rockridge",
			    KEY_FLG, iso9660->opt.rr);
		else if (iso9660->opt.rr == OPT_RR_STRICT)
			set_option_info(&info, &opt, "rockridge",
			    KEY_STR, "strict");
		else if (iso9660->opt.rr == OPT_RR_USEFUL)
			set_option_info(&info, &opt, "rockridge",
			    KEY_STR, "useful")