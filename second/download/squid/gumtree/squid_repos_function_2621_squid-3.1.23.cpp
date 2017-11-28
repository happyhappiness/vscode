void
debug_trap(const char *message)
{
    if (!opt_catch_signals)
        fatal_dump(message);

    _db_print("WARNING: %s\n", message);
}