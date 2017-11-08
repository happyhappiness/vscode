static int quit_cmd(void)
{
	string_list_clear(&del_list, 0);
	printf(_("Bye.\n"));
	return MENU_RETURN_NO_LOOP;
}