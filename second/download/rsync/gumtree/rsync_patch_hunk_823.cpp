 	}
 
 	return i;
 }
 
 
-static OFF_T parse_size_arg(const char *size_arg)
+static OFF_T parse_size_arg(char **size_arg, char def_suf)
 {
+	int reps, mult, make_compatible = 0;
 	const char *arg;
-	OFF_T size;
+	OFF_T size = 1;
 
-	for (arg = size_arg; isdigit(*(uchar*)arg); arg++) {}
+	for (arg = *size_arg; isdigit(*(uchar*)arg); arg++) {}
 	if (*arg == '.')
 		for (arg++; isdigit(*(uchar*)arg); arg++) {}
-	switch (*arg) {
+	switch (*arg && *arg != '+' && *arg != '-' ? *arg++ : def_suf) {
+	case 'b': case 'B':
+		reps = 0;
+		break;
 	case 'k': case 'K':
-		size = atof(size_arg) * 1024;
+		reps = 1;
 		break;
 	case 'm': case 'M':
-		size = atof(size_arg) * 1024*1024;
+		reps = 2;
 		break;
 	case 'g': case 'G':
-		size = atof(size_arg) * 1024*1024*1024;
-		break;
-	case '\0':
-		size = atof(size_arg);
+		reps = 3;
 		break;
 	default:
-		size = 0;
-		break;
+		return -1;
+	}
+	if (*arg == 'b' || *arg == 'B')
+		mult = 1000, make_compatible = 1, arg++;
+	else if (!*arg || *arg == '+' || *arg == '-')
+		mult = 1024;
+	else if (strncasecmp(arg, "ib", 2) == 0)
+		mult = 1024, arg += 2;
+	else
+		return -1;
+	while (reps--)
+		size *= mult;
+	size *= atof(*size_arg);
+	if ((*arg == '+' || *arg == '-') && arg[1] == '1')
+		size += atoi(arg), make_compatible = 1, arg += 2;
+	if (*arg)
+		return -1;
+	if (size > 0 && make_compatible) {
+		/* We convert this manually because we may need %lld precision,
+		 * and that's not a portable sprintf() escape. */
+		char buf[128], *s = buf + sizeof buf - 1;
+		OFF_T num = size;
+		*s = '\0';
+		while (num) {
+			*--s = (num % 10) + '0';
+			num /= 10;
+		}
+		if (!(*size_arg = strdup(s)))
+			out_of_memory("parse_size_arg");
 	}
 	return size;
 }
 
 
 static void create_refuse_error(int which)
