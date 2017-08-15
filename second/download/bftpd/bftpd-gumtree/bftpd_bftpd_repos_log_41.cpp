control_printf(SL_FAILURE, "230 Couldn't change cwd to '%s': %s.\r\n", str,
					 strerror(errno));