 #include "configfile.h"
 
 #if !KERNEL_LINUX
 # error "No applicable input method."
 #endif
 
-#define BUFSIZE 128
-
 /*
  * (Module-)Global variables
  */
 static const char *config_keys[] =
 {
 	"Irq",
 	"IgnoreSelected"
 };
 static int config_keys_num = STATIC_ARRAY_SIZE (config_keys);
 
-static unsigned int *irq_list;
-static unsigned int irq_list_num;
+static char         **irq_list;
+static unsigned int   irq_list_num = 0;
 
 /* 
  * irq_list_action:
  * 0 => default is to collect selected irqs
  * 1 => ignore selcted irqs
  */
 static int irq_list_action;
 
 static int irq_config (const char *key, const char *value)
 {
 	if (strcasecmp (key, "Irq") == 0)
 	{
-		unsigned int *temp;
-		unsigned int irq;
-		char *endptr;
+		char **temp;
 
-		temp = (unsigned int *) realloc (irq_list, (irq_list_num + 1) * sizeof (unsigned int *));
+		temp = realloc (irq_list, (irq_list_num + 1) * sizeof (*irq_list));
 		if (temp == NULL)
 		{
 			fprintf (stderr, "irq plugin: Cannot allocate more memory.\n");
 			ERROR ("irq plugin: Cannot allocate more memory.");
 			return (1);
 		}
 		irq_list = temp;
 
-		/* Clear errno, because we need it to see if an error occured. */
-		errno = 0;
-
-		irq = strtol(value, &endptr, 10);
-		if ((endptr == value) || (errno != 0))
+		irq_list[irq_list_num] = strdup (value);
+		if (irq_list[irq_list_num] == NULL)
 		{
-			fprintf (stderr, "irq plugin: Irq value is not a "
-					"number: `%s'\n", value);
-			ERROR ("irq plugin: Irq value is not a "
-					"number: `%s'", value);
+			ERROR ("irq plugin: strdup(3) failed.");
 			return (1);
 		}
-		irq_list[irq_list_num] = irq;
+
 		irq_list_num++;
 	}
 	else if (strcasecmp (key, "IgnoreSelected") == 0)
 	{
 		if (IS_TRUE (value))
 			irq_list_action = 1;
