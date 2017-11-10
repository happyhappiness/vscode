void set_error_routine(void (*routine)(const char *err, va_list params))
{
	error_routine = routine;
}