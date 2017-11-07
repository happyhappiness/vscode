static void parse_mark(void)
{
	if (starts_with(command_buf.buf, "mark :")) {
		next_mark = strtoumax(command_buf.buf + 6, NULL, 10);
		read_next_command();
	}
	else
		next_mark = 0;
}