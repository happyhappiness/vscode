static void setup_reference(void)
{
	for_each_string_list(&option_reference, add_one_reference, NULL);
}