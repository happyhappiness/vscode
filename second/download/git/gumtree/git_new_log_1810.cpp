status_printf_ln(s, color,
				Q_("Next command to do (%d remaining command):",
					"Next commands to do (%d remaining commands):",
					yet_to_do.nr),
				yet_to_do.nr);