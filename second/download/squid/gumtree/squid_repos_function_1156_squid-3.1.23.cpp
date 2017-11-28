static void
free_logformat(logformat ** definitions)
{
    while (*definitions) {
        logformat *format = *definitions;
        *definitions = format->next;
        safe_free(format->name);
        accessLogFreeLogFormat(&format->format);
        xfree(format);
    }
}