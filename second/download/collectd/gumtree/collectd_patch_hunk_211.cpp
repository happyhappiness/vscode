 				break;
 		}
 		else if (strchr (fields[i], '=') != NULL)
 		{
 			if (parse_option (&vl, fields[i]) != 0)
 			{
-				fprintf (fh, "-1 Error parsing option `%s'\n",
+				print_to_socket (fh, "-1 Error parsing option `%s'\n",
 						fields[i]);
 				break;
 			}
 		}
 		else
 		{
