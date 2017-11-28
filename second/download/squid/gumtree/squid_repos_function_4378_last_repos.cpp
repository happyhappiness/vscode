static void vlog(const char *level, const char *format, va_list args)
{
    time_t now = time(NULL);

    fprintf(logfile, "%ld %s| %s: ", static_cast<long int>(now),
            program_name, level);
    vfprintf (logfile, format, args);
    fflush(logfile);
}