static void die_initial_contact(int got_at_least_one_head)
{
	if (got_at_least_one_head)
		die("The remote end hung up upon initial contact");
	else
		die("Could not read from remote repository.\n\n"
		    "Please make sure you have the correct access rights\n"
		    "and the repository exists.");
}