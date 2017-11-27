{
	"Irq",
	"IgnoreSelected"
};
static int config_keys_num = STATIC_ARRAY_SIZE (config_keys);

static ignorelist_t *ignorelist = NULL;

/*
 * Private functions
 */
static int irq_config (const char *key, const char *value)
{
	if (ignorelist == NULL)
		ignorelist = ignorelist_create (/* invert = */ 1);

	if (strcasecmp (key, "Irq") == 0)
	{
		ignorelist_add (ignorelist, value);
	}
	else if (strcasecmp (key, "IgnoreSelected") == 0)
	{
		int invert = 1;
		if (IS_TRUE (value))
			invert = 0;
		ignorelist_set_invert (ignorelist, invert);
	}
	else
	{
		return (-1);
	}

	return (0);
}

static void irq_submit (const char *irq_name, derive_t value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	if (ignorelist_match (ignorelist, irq_name) != 0)
		return;

	values[0].derive = value;

	vl.values = values;
	vl.values_len = 1;
