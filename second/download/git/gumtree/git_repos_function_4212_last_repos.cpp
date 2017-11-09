void set_warn_routine(void (*routine)(const char *warn, va_list params))
{
	warn_routine = routine;
}