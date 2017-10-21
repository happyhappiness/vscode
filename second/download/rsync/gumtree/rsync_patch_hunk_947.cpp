 				*t++ = toLower(f);
 			else
 				*t++ = *f;
 		} while (*++f != '/' && *f);
 		*t++ = '\0';
 
-		fprintf(stderr, "adding `%s'\n", buf);
 		add_suffix(&suftree, *buf, buf+1);
 	}
 
 	free(buf);
 }
 
