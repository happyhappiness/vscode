{
			if (strncasecmp(foo, "yes", 3))
				control_printf(SL_FAILURE, "530-Server disabled.\r\n421 Reason: %s", foo);
			else
				control_printf(SL_FAILURE, "530 Login incorrect.");
			bftpd_log("Login as user '%s' failed: Server disabled.\n", user);
			exit(0);
		}