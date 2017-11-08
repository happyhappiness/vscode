static void die_no_single_rev(int quiet)
{
	if (quiet)
		exit(1);
	else
		die("Needed a single revision");
}