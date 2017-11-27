 		fprintf (stderr, "Cannot set the interval to a correct value.\n"
 				"Please check your settings.\n");
 		return (-1);
 	}
 	DEBUG ("interval_g = %i;", interval_g);
 
+	str = global_option_get ("Timeout");
+	if (str == NULL)
+		str = "2";
+	timeout_g = atoi (str);
+	if (timeout_g <= 1)
+	{
+		fprintf (stderr, "Cannot set the timeout to a correct value.\n"
+				"Please check your settings.\n");
+		return (-1);
+	}
+	DEBUG ("timeout_g = %i;", timeout_g);
+
 	if (init_hostname () != 0)
 		return (-1);
 	DEBUG ("hostname_g = %s;", hostname_g);
 
 	return (0);
 } /* int init_global_variables */
