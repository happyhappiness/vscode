static void
_db_print_file(const char *format, va_list args)
{
    if (debug_log == NULL)
        return;

    /* give a chance to context-based debugging to print current context */
    if (!Ctx_Lock)
        ctx_print();

    vfprintf(debug_log, format, args);
    fflush(debug_log);
}