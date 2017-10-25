char *getpass(const char *prompt)
{
	static char password[80];
	printf(prompt);
	gets(password);
	return password;
}