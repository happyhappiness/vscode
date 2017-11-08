static int is_valid_cmd_name(const char *cmd)
{
	/* Test command contains no . or / characters */
	return cmd[strcspn(cmd, "./")] == '\0';
}