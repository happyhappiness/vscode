static void get_text_file(char *name)
{
	select_getanyfile();
	hdr_nocache();
	send_local_file("text/plain", name);
}