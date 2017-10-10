 			*prefix_len = strtol(pos + 7, &endptr, 10);
 			if (endptr - pos != len)
 				die(_("invalid parameter for pathspec magic 'prefix'"));
 			continue;
 		}
 
+		if (starts_with(pos, "attr:")) {
+			char *attr_body = xmemdupz(pos + 5, len - 5);
+			parse_pathspec_attr_match(item, attr_body);
+			*magic |= PATHSPEC_ATTR;
+			free(attr_body);
+			continue;
+		}
+
 		for (i = 0; i < ARRAY_SIZE(pathspec_magic); i++) {
 			if (strlen(pathspec_magic[i].name) == len &&
 			    !strncmp(pathspec_magic[i].name, pos, len)) {
 				*magic |= pathspec_magic[i].bit;
 				break;
 			}
