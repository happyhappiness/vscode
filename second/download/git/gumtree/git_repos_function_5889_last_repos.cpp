static void setup_reference(void)
{
	int required = 1;
	for_each_string_list(&option_required_reference,
			     add_one_reference, &required);
	required = 0;
	for_each_string_list(&option_optional_reference,
			     add_one_reference, &required);
}