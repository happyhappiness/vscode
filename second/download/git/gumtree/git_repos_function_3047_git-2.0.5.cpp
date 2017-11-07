void set_die_is_recursing_routine(int (*routine)(void))
{
	die_is_recursing = routine;
}