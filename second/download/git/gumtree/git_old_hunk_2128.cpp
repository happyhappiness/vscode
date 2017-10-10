				 namlen, dir, user_path, restlen, slash);
			dir = rpath;
		}
	}
	else if (interpolated_path && saw_extended_args) {
		struct strbuf expanded_path = STRBUF_INIT;
		struct strbuf_expand_dict_entry dict[6];

		dict[0].placeholder = "H"; dict[0].value = hostname;
		dict[1].placeholder = "CH"; dict[1].value = canon_hostname;
		dict[2].placeholder = "IP"; dict[2].value = ip_address;
		dict[3].placeholder = "P"; dict[3].value = tcp_port;
		dict[4].placeholder = "D"; dict[4].value = directory;
		dict[5].placeholder = NULL; dict[5].value = NULL;
		if (*dir != '/') {
			/* Allow only absolute */
			logerror("'%s': Non-absolute path denied (interpolated-path active)", dir);
			return NULL;
		}

		strbuf_expand(&expanded_path, interpolated_path,
				strbuf_expand_dict_cb, &dict);
		strlcpy(interp_path, expanded_path.buf, PATH_MAX);
		strbuf_release(&expanded_path);
		loginfo("Interpolated dir '%s'", interp_path);

		dir = interp_path;
	}
