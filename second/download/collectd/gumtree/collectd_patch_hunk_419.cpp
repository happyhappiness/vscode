 {
 	"Irq",
 	"IgnoreSelected"
 };
 static int config_keys_num = STATIC_ARRAY_SIZE (config_keys);
 
-static char         **irq_list;
-static unsigned int   irq_list_num = 0;
+static ignorelist_t *ignorelist = NULL;
 
-/* 
- * irq_list_action:
- * 0 => default is to collect selected irqs
- * 1 => ignore selcted irqs
+/*
+ * Private functions
  */
-static int irq_list_action;
-
 static int irq_config (const char *key, const char *value)
 {
+	if (ignorelist == NULL)
+		ignorelist = ignorelist_create (/* invert = */ 1);
+
 	if (strcasecmp (key, "Irq") == 0)
 	{
-		char **temp;
-
-		temp = realloc (irq_list, (irq_list_num + 1) * sizeof (*irq_list));
-		if (temp == NULL)
-		{
-			fprintf (stderr, "irq plugin: Cannot allocate more memory.\n");
-			ERROR ("irq plugin: Cannot allocate more memory.");
-			return (1);
-		}
-		irq_list = temp;
-
-		irq_list[irq_list_num] = strdup (value);
-		if (irq_list[irq_list_num] == NULL)
-		{
-			ERROR ("irq plugin: strdup(3) failed.");
-			return (1);
-		}
-
-		irq_list_num++;
+		ignorelist_add (ignorelist, value);
 	}
 	else if (strcasecmp (key, "IgnoreSelected") == 0)
 	{
+		int invert = 1;
 		if (IS_TRUE (value))
-			irq_list_action = 1;
-		else
-			irq_list_action = 0;
+			invert = 0;
+		ignorelist_set_invert (ignorelist, invert);
 	}
 	else
 	{
 		return (-1);
 	}
-	return (0);
-}
-
-/*
- * Check if this interface/instance should be ignored. This is called from
- * both, `submit' and `write' to give client and server the ability to
- * ignore certain stuff..
- */
-static int check_ignore_irq (const char *irq)
-{
-	unsigned int i;
 
-	if (irq_list_num < 1)
-		return (0);
-
-	for (i = 0; i < irq_list_num; i++)
-		if (strcmp (irq, irq_list[i]) == 0)
-			return (irq_list_action);
-
-	return (1 - irq_list_action);
+	return (0);
 }
 
 static void irq_submit (const char *irq_name, derive_t value)
 {
 	value_t values[1];
 	value_list_t vl = VALUE_LIST_INIT;
 
-	if (check_ignore_irq (irq_name))
+	if (ignorelist_match (ignorelist, irq_name) != 0)
 		return;
 
 	values[0].derive = value;
 
 	vl.values = values;
 	vl.values_len = 1;
