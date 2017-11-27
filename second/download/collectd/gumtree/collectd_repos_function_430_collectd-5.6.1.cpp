static int mr_config_add_regex (mr_regex_t **re_head, /* {{{ */
		oconfig_item_t *ci)
{
	mr_regex_t *re;
	int status;

	if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
	{
		log_warn ("`%s' needs exactly one string argument.", ci->key);
		return (-1);
	}

	re = calloc (1, sizeof (*re));
	if (re == NULL)
	{
		log_err ("mr_config_add_regex: calloc failed.");
		return (-1);
	}
	re->next = NULL;

	re->re_str = strdup (ci->values[0].value.string);
	if (re->re_str == NULL)
	{
		free (re);
		log_err ("mr_config_add_regex: strdup failed.");
		return (-1);
	}

	status = regcomp (&re->re, re->re_str, REG_EXTENDED | REG_NOSUB);
	if (status != 0)
	{
		char errmsg[1024];
		regerror (status, &re->re, errmsg, sizeof (errmsg));
		errmsg[sizeof (errmsg) - 1] = 0;
		log_err ("Compiling regex `%s' for `%s' failed: %s.",
				re->re_str, ci->key, errmsg);
		free (re->re_str);
		free (re);
		return (-1);
	}

	if (*re_head == NULL)
	{
		*re_head = re;
	}
	else
	{
		mr_regex_t *ptr;

		ptr = *re_head;
		while (ptr->next != NULL)
			ptr = ptr->next;

		ptr->next = re;
	}

	return (0);
}