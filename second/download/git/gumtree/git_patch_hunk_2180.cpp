 	int i;
 
 	if (len < 0)
 		len = strlen(str);
 
 	for (i = 1; i < ARRAY_SIZE(object_type_strings); i++)
-		if (!strncmp(str, object_type_strings[i], len))
+		if (!strncmp(str, object_type_strings[i], len) &&
+		    object_type_strings[i][len] == '\0')
 			return i;
 
 	if (gentle)
 		return -1;
 
 	die("invalid object type \"%s\"", str);
