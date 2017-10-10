				if (value && !strcasecmp(value, "if-asked"))
					set_push_cert_flags(flags, SEND_PACK_PUSH_CERT_IF_ASKED);
				else
					return error("Invalid value for '%s'", k);
			}
		}
	}

	return git_default_config(k, v, NULL);
}

int cmd_push(int argc, const char **argv, const char *prefix)
