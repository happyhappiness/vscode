void command_errf(sed_commands_t *commands, const char *fmt, ...)
{
    if (commands->errfn && commands->pool) {
        va_list args;
        const char* error;
        va_start(args, fmt);
        error = apr_pvsprintf(commands->pool, fmt, args);
        commands->errfn(commands->data, error);
        va_end(args);
    }
}