static const uchar *rule_strcmp(const uchar *str, const char *rule, int rule_len)
{
	if (strncmp((char*)str, rule, rule_len) != 0)
		return NULL;
	if (isspace(str[rule_len]) || str[rule_len] == '_' || !str[rule_len])
		return str + rule_len - 1;
	if (str[rule_len] == ',')
		return str + rule_len;
	return NULL;
}