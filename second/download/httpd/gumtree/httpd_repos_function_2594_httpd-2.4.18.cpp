static void comperr(sed_commands_t *commands, char *msg)
{
    command_errf(commands, msg, commands->linebuf);
}