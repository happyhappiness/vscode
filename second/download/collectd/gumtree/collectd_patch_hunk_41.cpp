 		}
 	}
 
 	return (0);
 }
 
-int rrd_create_file (char *filename, char **ds_def, int ds_num)
+/* * * * *
+ * Magic *
+ * * * * */
+#if HAVE_LIBRRD
+static int rra_get (char ***ret)
+{
+	static char **rra_def = NULL;
+	static int rra_num = 0;
+
+	int rra_max = rra_timespans_num * rra_types_num;
+
+	int step;
+	int rows;
+	int span;
+
+	int cdp_num;
+	int cdp_len;
+	int i, j;
+
+	char buffer[64];
+
+	if ((rra_num != 0) && (rra_def != NULL))
+	{
+		*ret = rra_def;
+		return (rra_num);
+	}
+
+	if ((rra_def = (char **) malloc ((rra_max + 1) * sizeof (char *))) == NULL)
+		return (-1);
+	memset (rra_def, '\0', (rra_max + 1) * sizeof (char *));
+
+	step = atoi (COLLECTD_STEP);
+	rows = atoi (COLLECTD_ROWS);
+
+	if ((step <= 0) || (rows <= 0))
+	{
+		*ret = NULL;
+		return (-1);
+	}
+
+	cdp_len = 0;
+	for (i = 0; i < rra_timespans_num; i++)
+	{
+		span = rra_timespans[i];
+
+		if ((span / step) < rows)
+			continue;
+
+		if (cdp_len == 0)
+			cdp_len = 1;
+		else
+			cdp_len = (int) floor (((double) span) / ((double) (rows * step)));
+
+		cdp_num = (int) ceil (((double) span) / ((double) (cdp_len * step)));
+
+		for (j = 0; j < rra_types_num; j++)
+		{
+			if (rra_num >= rra_max)
+				break;
+
+			if (snprintf (buffer, sizeof(buffer), "RRA:%s:%3.1f:%u:%u",
+						rra_types[j], COLLECTD_XFF,
+						cdp_len, cdp_num) >= sizeof (buffer))
+			{
+				syslog (LOG_ERR, "rra_get: Buffer would have been truncated.");
+				continue;
+			}
+
+			rra_def[rra_num++] = sstrdup (buffer);
+		}
+	}
+
+#if COLLECT_DEBUG
+	DBG ("rra_num = %i", rra_num);
+	for (i = 0; i < rra_num; i++)
+		DBG ("  %s", rra_def[i]);
+#endif
+
+	*ret = rra_def;
+	return (rra_num);
+}
+#endif /* HAVE_LIBRRD */
+
+static int log_create_file (char *filename, char **ds_def, int ds_num)
+{
+	FILE *log;
+	int i;
+
+	if (check_create_dir (filename))
+		return (-1);
+
+	log = fopen (filename, "w");
+	if (log == NULL)
+	{
+		syslog (LOG_WARNING, "Failed to create %s: %s", filename,
+				strerror(errno));
+		return (-1);
+	}
+
+	fprintf (log, "epoch");
+	for (i = 0; i < ds_num; i++)
+	{
+		char *name;
+		char *tmp;
+
+		name = strchr (ds_def[i], ':');
+		if (name == NULL)
+		{
+			syslog (LOG_WARNING, "Invalid DS definition '%s' for %s",
+					ds_def[i], filename);
+			fclose(log);
+			remove(filename);
+			return (-1);
+		}
+
+		name += 1;
+		tmp = strchr (name, ':');
+		if (tmp == NULL)
+		{
+			syslog (LOG_WARNING, "Invalid DS definition '%s' for %s",
+					ds_def[i], filename);
+			fclose(log);
+			remove(filename);
+			return (-1);
+		}
+
+		/* The `%.*s' is needed because there is no null-byte behind
+		 * the name. */
+		fprintf(log, ",%.*s", (tmp - name), name);
+	}
+	fprintf(log, "\n");
+	fclose(log);
+
+	return 0;
+}
+
+static int log_update_file (char *host, char *file, char *values,
+		char **ds_def, int ds_num)
+{
+	char *tmp;
+	FILE *fp;
+	struct stat statbuf;
+	char full_file[1024];
+
+	/* Cook the values a bit: Substitute colons with commas */
+	strsubstitute (values, ':', ',');
+
+	/* host == NULL => local mode */
+	if (host != NULL)
+	{
+		if (snprintf (full_file, 1024, "%s/%s", host, file) >= 1024)
+			return (-1);
+	}
+	else
+	{
+		if (snprintf (full_file, 1024, "%s", file) >= 1024)
+			return (-1);
+	}
+
+	strncpy (full_file, file, 1024);
+
+	tmp = full_file + strlen (full_file) - 4;
+	assert (tmp > 0);
+
+	/* Change the filename for logfiles. */
+	if (strncmp (tmp, ".rrd", 4) == 0)
+	{
+		time_t now;
+		struct tm *tm;
+
+		/* TODO: Find a way to minimize the calls to `localtime', since
+		 * they are pretty expensive.. */
+		now = time (NULL);
+		tm = localtime (&now);
+
+		strftime (tmp, 1024 - (tmp - full_file), "-%Y-%m-%d", tm);
+
+		/* `localtime(3)' returns a pointer to static data,
+		 * therefore the pointer may not be free'd. */
+	}
+	else
+		DBG ("The filename ends with `%s' which is unexpected.", tmp);
+
+	if (stat (full_file, &statbuf) == -1)
+	{
+		if (errno == ENOENT)
+		{
+			if (log_create_file (full_file, ds_def, ds_num))
+				return (-1);
+		}
+		else
+		{
+			syslog (LOG_ERR, "stat %s: %s", full_file, strerror (errno));
+			return (-1);
+		}
+	}
+	else if (!S_ISREG (statbuf.st_mode))
+	{
+		syslog (LOG_ERR, "stat %s: Not a regular file!", full_file);
+		return (-1);
+	}
+
+
+	fp = fopen (full_file, "a");
+	if (fp == NULL)
+	{
+		syslog (LOG_WARNING, "Failed to append to %s: %s", full_file,
+				strerror(errno));
+		return (-1);
+	}
+	fprintf(fp, "%s\n", values);
+	fclose(fp);
+
+	return (0);
+} /* int log_update_file */
+
+#if HAVE_LIBRRD
+static int rrd_create_file (char *filename, char **ds_def, int ds_num)
 {
 	char **argv;
 	int argc;
+	char **rra_def;
+	int rra_num;
 	int i, j;
 	int status = 0;
 
 	if (check_create_dir (filename))
 		return (-1);
 
+	if ((rra_num = rra_get (&rra_def)) < 1)
+	{
+		syslog (LOG_ERR, "rra_create failed: Could not calculate RRAs");
+		return (-1);
+	}
+
 	argc = ds_num + rra_num + 4;
 
 	if ((argv = (char **) malloc (sizeof (char *) * (argc + 1))) == NULL)
 	{
 		syslog (LOG_ERR, "rrd_create failed: %s", strerror (errno));
 		return (-1);
 	}
 
 	argv[0] = "create";
 	argv[1] = filename;
 	argv[2] = "-s";
-	argv[3] = "10";
+	argv[3] = COLLECTD_STEP;
 
 	j = 4;
 	for (i = 0; i < ds_num; i++)
 		argv[j++] = ds_def[i];
 	for (i = 0; i < rra_num; i++)
 		argv[j++] = rra_def[i];
