 
 		if ((hostname_g != NULL) && (strcasecmp (hostname_g, ret_ident[i].host)))
 			continue;
 
 		if ((hostname == NULL) || strcasecmp (hostname, ret_ident[i].host))
 		{
-			if (hostname != NULL)
-				free (hostname);
+			free (hostname);
 			hostname = strdup (ret_ident[i].host);
 			printf ("Host: %s\n", hostname);
 		}
 
 		/* empty hostname; not to be printed again */
 		ret_ident[i].host[0] = '\0';
