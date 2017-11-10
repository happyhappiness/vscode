static int ident_is_sufficient(int user_ident_explicitly_given)
{
#ifndef WINDOWS
	return (user_ident_explicitly_given & IDENT_MAIL_GIVEN);
#else
	return (user_ident_explicitly_given == IDENT_ALL_GIVEN);
#endif
}