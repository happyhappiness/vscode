 
 		if (starts_with(name, "refname"))
 			refname = ref->refname;
 		else if (starts_with(name, "symref"))
 			refname = ref->symref ? ref->symref : "";
 		else if (starts_with(name, "upstream")) {
+			const char *branch_name;
 			/* only local branches may have an upstream */
-			if (!starts_with(ref->refname, "refs/heads/"))
+			if (!skip_prefix(ref->refname, "refs/heads/",
+					 &branch_name))
 				continue;
-			branch = branch_get(ref->refname + 11);
+			branch = branch_get(branch_name);
 
-			if (!branch || !branch->merge || !branch->merge[0] ||
-			    !branch->merge[0]->dst)
+			refname = branch_get_upstream(branch, NULL);
+			if (!refname)
+				continue;
+		} else if (starts_with(name, "push")) {
+			const char *branch_name;
+			if (!skip_prefix(ref->refname, "refs/heads/",
+					 &branch_name))
+				continue;
+			branch = branch_get(branch_name);
+
+			refname = branch_get_push(branch, NULL);
+			if (!refname)
 				continue;
-			refname = branch->merge[0]->dst;
 		} else if (starts_with(name, "color:")) {
 			char color[COLOR_MAXLEN] = "";
 
 			if (color_parse(name + 6, color) < 0)
 				die(_("unable to parse format"));
 			v->s = xstrdup(color);
