				if (opts.version > 2)
					die(_("bad %s"), arg);
				if (*c == ',')
					opts.off32_limit = strtoul(c+1, &c, 0);
				if (*c || opts.off32_limit & 0x80000000)
					die(_("bad %s"), arg);
			} else
				usage(index_pack_usage);
			continue;
		}

		if (pack_name)
