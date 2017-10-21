/****************************************************************************
set user socket options
****************************************************************************/
void set_socket_options(int fd, char *options)
{
	char *tok;
	options = strdup(options);
	
	if (!options) out_of_memory("set_socket_options");

	for (tok=strtok(options, " \t,"); tok; tok=strtok(NULL," \t,")) {
		int ret=0,i;
