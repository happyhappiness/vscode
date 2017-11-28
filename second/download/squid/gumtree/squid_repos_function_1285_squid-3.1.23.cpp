void
String::reset(const char *str)
{
    PROF_start(StringReset);
    clean(); // TODO: optimize to avoid cleaning the buffer if we can reuse it
    if (str)
        allocAndFill(str, strlen(str));
    PROF_stop(StringReset);
}