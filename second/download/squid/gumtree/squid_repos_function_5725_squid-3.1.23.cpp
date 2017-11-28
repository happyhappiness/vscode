void
default_failure_notify(const char *message)
{
    if (write(2, message, strlen(message))) {}
    if (write(2, "\n", 1)) {}
    abort();
}