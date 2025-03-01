 static char **match_ds_g = NULL;
 static size_t match_ds_num_g = 0;
 
 /* `strdup' is an XSI extension. I don't want to pull in all of XSI just for
  * that, so here's an own implementation.. It's easy enough. The GCC attributes
  * are supposed to get good performance..  -octo */
-__attribute__((malloc, nonnull (1)))
-static char *cn_strdup (const char *str) /* {{{ */
+__attribute__((malloc, nonnull(1))) static char *
+cn_strdup(const char *str) /* {{{ */
 {
   size_t strsize;
   char *ret;
 
-  strsize = strlen (str) + 1;
-  ret = (char *) malloc (strsize);
+  strsize = strlen(str) + 1;
+  ret = (char *)malloc(strsize);
   if (ret != NULL)
-    memcpy (ret, str, strsize);
+    memcpy(ret, str, strsize);
   return (ret);
 } /* }}} char *cn_strdup */
 
-static int filter_ds (size_t *values_num,
-		double **values, char ***values_names)
-{
-	gauge_t *new_values;
-	char   **new_names;
-
-	if (match_ds_g == NULL)
-		return (RET_OKAY);
-
-	new_values = (gauge_t *)calloc (match_ds_num_g, sizeof (*new_values));
-	if (new_values == NULL)
-	{
-		fprintf (stderr, "calloc failed: %s\n", strerror (errno));
-		return (RET_UNKNOWN);
-	}
-
-	new_names = (char **)calloc (match_ds_num_g, sizeof (*new_names));
-	if (new_names == NULL)
-	{
-		fprintf (stderr, "calloc failed: %s\n", strerror (errno));
-		free (new_values);
-		return (RET_UNKNOWN);
-	}
-
-	for (size_t i = 0; i < match_ds_num_g; i++)
-	{
-		size_t j;
-
-		/* match_ds_g keeps pointers into argv but the names will be freed */
-		new_names[i] = cn_strdup (match_ds_g[i]);
-		if (new_names[i] == NULL)
-		{
-			fprintf (stderr, "cn_strdup failed: %s\n", strerror (errno));
-			free (new_values);
-			for (j = 0; j < i; j++)
-				free (new_names[j]);
-			free (new_names);
-			return (RET_UNKNOWN);
-		}
-
-		for (j = 0; j < *values_num; j++)
-			if (strcasecmp (new_names[i], (*values_names)[j]) == 0)
-				break;
-
-		if (j == *values_num)
-		{
-			printf ("ERROR: DS `%s' is not available.\n", new_names[i]);
-			free (new_values);
-			for (j = 0; j <= i; j++)
-				free (new_names[j]);
-			free (new_names);
-			return (RET_CRITICAL);
-		}
-
-		new_values[i] = (*values)[j];
-	}
-
-	free (*values);
-	for (size_t i = 0; i < *values_num; i++)
-		free ((*values_names)[i]);
-	free (*values_names);
-
-	*values       = new_values;
-	*values_names = new_names;
-	*values_num   = match_ds_num_g;
-	return (RET_OKAY);
+static int filter_ds(size_t *values_num, double **values,
+                     char ***values_names) {
+  gauge_t *new_values;
+  char **new_names;
+
+  if (match_ds_g == NULL)
+    return (RET_OKAY);
+
+  new_values = (gauge_t *)calloc(match_ds_num_g, sizeof(*new_values));
+  if (new_values == NULL) {
+    fprintf(stderr, "calloc failed: %s\n", strerror(errno));
+    return (RET_UNKNOWN);
+  }
+
+  new_names = (char **)calloc(match_ds_num_g, sizeof(*new_names));
+  if (new_names == NULL) {
+    fprintf(stderr, "calloc failed: %s\n", strerror(errno));
+    free(new_values);
+    return (RET_UNKNOWN);
+  }
+
+  for (size_t i = 0; i < match_ds_num_g; i++) {
+    size_t j;
+
+    /* match_ds_g keeps pointers into argv but the names will be freed */
+    new_names[i] = cn_strdup(match_ds_g[i]);
+    if (new_names[i] == NULL) {
+      fprintf(stderr, "cn_strdup failed: %s\n", strerror(errno));
+      free(new_values);
+      for (j = 0; j < i; j++)
+        free(new_names[j]);
+      free(new_names);
+      return (RET_UNKNOWN);
+    }
+
+    for (j = 0; j < *values_num; j++)
+      if (strcasecmp(new_names[i], (*values_names)[j]) == 0)
+        break;
+
+    if (j == *values_num) {
+      printf("ERROR: DS `%s' is not available.\n", new_names[i]);
+      free(new_values);
+      for (j = 0; j <= i; j++)
+        free(new_names[j]);
+      free(new_names);
+      return (RET_CRITICAL);
+    }
+
+    new_values[i] = (*values)[j];
+  }
+
+  free(*values);
+  for (size_t i = 0; i < *values_num; i++)
+    free((*values_names)[i]);
+  free(*values_names);
+
+  *values = new_values;
+  *values_names = new_names;
+  *values_num = match_ds_num_g;
+  return (RET_OKAY);
 } /* int filter_ds */
 
-static void parse_range (char *string, range_t *range)
-{
-	char *min_ptr;
-	char *max_ptr;
-
-	if (*string == '@')
-	{
-		range->invert = 1;
-		string++;
-	}
-
-	max_ptr = strchr (string, ':');
-	if (max_ptr == NULL)
-	{
-		min_ptr = NULL;
-		max_ptr = string;
-	}
-	else
-	{
-		min_ptr = string;
-		*max_ptr = '\0';
-		max_ptr++;
-	}
-
-	assert (max_ptr != NULL);
-
-	/* `10' == `0:10' */
-	if (min_ptr == NULL)
-		range->min = 0.0;
-	/* :10 == ~:10 == -inf:10 */
-	else if ((*min_ptr == '\0') || (*min_ptr == '~'))
-		range->min = NAN;
-	else
-		range->min = atof (min_ptr);
-
-	if ((*max_ptr == '\0') || (*max_ptr == '~'))
-		range->max = NAN;
-	else
-		range->max = atof (max_ptr);
+static void parse_range(char *string, range_t *range) {
+  char *min_ptr;
+  char *max_ptr;
+
+  if (*string == '@') {
+    range->invert = 1;
+    string++;
+  }
+
+  max_ptr = strchr(string, ':');
+  if (max_ptr == NULL) {
+    min_ptr = NULL;
+    max_ptr = string;
+  } else {
+    min_ptr = string;
+    *max_ptr = '\0';
+    max_ptr++;
+  }
+
+  assert(max_ptr != NULL);
+
+  /* `10' == `0:10' */
+  if (min_ptr == NULL)
+    range->min = 0.0;
+  /* :10 == ~:10 == -inf:10 */
+  else if ((*min_ptr == '\0') || (*min_ptr == '~'))
+    range->min = NAN;
+  else
+    range->min = atof(min_ptr);
+
+  if ((*max_ptr == '\0') || (*max_ptr == '~'))
+    range->max = NAN;
+  else
+    range->max = atof(max_ptr);
 } /* void parse_range */
 
-static int match_range (range_t *range, double value)
-{
-	int ret = 0;
+static int match_range(range_t *range, double value) {
+  int ret = 0;
 
-	if (!isnan (range->min) && (range->min > value))
-		ret = 1;
-	if (!isnan (range->max) && (range->max < value))
-		ret = 1;
+  if (!isnan(range->min) && (range->min > value))
+    ret = 1;
+  if (!isnan(range->max) && (range->max < value))
+    ret = 1;
 
-	return (((ret - range->invert) == 0) ? 0 : 1);
+  return (((ret - range->invert) == 0) ? 0 : 1);
 } /* int match_range */
 
-__attribute__((noreturn))
-static void usage (const char *name)
-{
-	fprintf (stderr, "Usage: %s <-s socket> <-n value_spec> <-H hostname> [options]\n"
-			"\n"
-			"Valid options are:\n"
-			"  -s <socket>    Path to collectd's UNIX-socket.\n"
-			"  -n <v_spec>    Value specification to get from collectd.\n"
-			"                 Format: `plugin-instance/type-instance'\n"
-			"  -d <ds>        Select the DS to examine. May be repeated to examine multiple\n"
-			"                 DSes. By default all DSes are used.\n"
-			"  -g <consol>    Method to use to consolidate several DSes.\n"
-			"                 See below for a list of valid arguments.\n"
-			"  -H <host>      Hostname to query the values for.\n"
-			"  -c <range>     Critical range\n"
-			"  -w <range>     Warning range\n"
-			"  -m             Treat \"Not a Number\" (NaN) as critical (default: warning)\n"
-			"\n"
-			"Consolidation functions:\n"
-			"  none:          Apply the warning- and critical-ranges to each data-source\n"
-			"                 individually.\n"
-			"  average:       Calculate the average of all matching DSes and apply the\n"
-			"                 warning- and critical-ranges to the calculated average.\n"
-			"  sum:           Apply the ranges to the sum of all DSes.\n"
-			"  percentage:    Apply the ranges to the ratio (in percent) of the first value\n"
-			"                 and the sum of all values."
-			"\n", name);
-	exit (1);
+__attribute__((noreturn)) static void usage(const char *name) {
+  fprintf(stderr,
+          "Usage: %s <-s socket> <-n value_spec> <-H hostname> [options]\n"
+          "\n"
+          "Valid options are:\n"
+          "  -s <socket>    Path to collectd's UNIX-socket.\n"
+          "  -n <v_spec>    Value specification to get from collectd.\n"
+          "                 Format: `plugin-instance/type-instance'\n"
+          "  -d <ds>        Select the DS to examine. May be repeated to "
+          "examine multiple\n"
+          "                 DSes. By default all DSes are used.\n"
+          "  -g <consol>    Method to use to consolidate several DSes.\n"
+          "                 See below for a list of valid arguments.\n"
+          "  -H <host>      Hostname to query the values for.\n"
+          "  -c <range>     Critical range\n"
+          "  -w <range>     Warning range\n"
+          "  -m             Treat \"Not a Number\" (NaN) as critical (default: "
+          "warning)\n"
+          "\n"
+          "Consolidation functions:\n"
+          "  none:          Apply the warning- and critical-ranges to each "
+          "data-source\n"
+          "                 individually.\n"
+          "  average:       Calculate the average of all matching DSes and "
+          "apply the\n"
+          "                 warning- and critical-ranges to the calculated "
+          "average.\n"
+          "  sum:           Apply the ranges to the sum of all DSes.\n"
+          "  percentage:    Apply the ranges to the ratio (in percent) of the "
+          "first value\n"
+          "                 and the sum of all values."
+          "\n",
+          name);
+  exit(1);
 } /* void usage */
 
-static int do_listval (lcc_connection_t *connection)
-{
-	lcc_identifier_t *ret_ident = NULL;
-	size_t ret_ident_num = 0;
-
-	char *hostname = NULL;
-
-	int status;
-
-	status = lcc_listval (connection, &ret_ident, &ret_ident_num);
-	if (status != 0) {
-		printf ("UNKNOWN: %s\n", lcc_strerror (connection));
-		if (ret_ident != NULL)
-			free (ret_ident);
-		return (RET_UNKNOWN);
-	}
-
-	status = lcc_sort_identifiers (connection, ret_ident, ret_ident_num);
-	if (status != 0) {
-		printf ("UNKNOWN: %s\n", lcc_strerror (connection));
-		if (ret_ident != NULL)
-			free (ret_ident);
-		return (RET_UNKNOWN);
-	}
-
-	for (size_t i = 0; i < ret_ident_num; ++i) {
-		char id[1024];
-
-		if ((hostname_g != NULL) && (strcasecmp (hostname_g, ret_ident[i].host)))
-			continue;
-
-		if ((hostname == NULL) || strcasecmp (hostname, ret_ident[i].host))
-		{
-			free (hostname);
-			hostname = strdup (ret_ident[i].host);
-			printf ("Host: %s\n", hostname);
-		}
-
-		/* empty hostname; not to be printed again */
-		ret_ident[i].host[0] = '\0';
-
-		status = lcc_identifier_to_string (connection,
-				id, sizeof (id), ret_ident + i);
-		if (status != 0) {
-			printf ("ERROR: listval: Failed to convert returned "
-					"identifier to a string: %s\n",
-					lcc_strerror (connection));
-			free (hostname);
-			hostname = NULL;
-			continue;
-		}
-
-		/* skip over the (empty) hostname and following '/' */
-		printf ("\t%s\n", id + 1);
-	}
-
-	free (ret_ident);
-	free (hostname);
-	return (RET_OKAY);
+static int do_listval(lcc_connection_t *connection) {
+  lcc_identifier_t *ret_ident = NULL;
+  size_t ret_ident_num = 0;
+
+  char *hostname = NULL;
+
+  int status;
+
+  status = lcc_listval(connection, &ret_ident, &ret_ident_num);
+  if (status != 0) {
+    printf("UNKNOWN: %s\n", lcc_strerror(connection));
+    if (ret_ident != NULL)
+      free(ret_ident);
+    return (RET_UNKNOWN);
+  }
+
+  status = lcc_sort_identifiers(connection, ret_ident, ret_ident_num);
+  if (status != 0) {
+    printf("UNKNOWN: %s\n", lcc_strerror(connection));
+    if (ret_ident != NULL)
+      free(ret_ident);
+    return (RET_UNKNOWN);
+  }
+
+  for (size_t i = 0; i < ret_ident_num; ++i) {
+    char id[1024];
+
+    if ((hostname_g != NULL) && (strcasecmp(hostname_g, ret_ident[i].host)))
+      continue;
+
+    if ((hostname == NULL) || strcasecmp(hostname, ret_ident[i].host)) {
+      free(hostname);
+      hostname = strdup(ret_ident[i].host);
+      printf("Host: %s\n", hostname);
+    }
+
+    /* empty hostname; not to be printed again */
+    ret_ident[i].host[0] = '\0';
+
+    status =
+        lcc_identifier_to_string(connection, id, sizeof(id), ret_ident + i);
+    if (status != 0) {
+      printf("ERROR: listval: Failed to convert returned "
+             "identifier to a string: %s\n",
+             lcc_strerror(connection));
+      free(hostname);
+      hostname = NULL;
+      continue;
+    }
+
+    /* skip over the (empty) hostname and following '/' */
+    printf("\t%s\n", id + 1);
+  }
+
+  free(ret_ident);
+  free(hostname);
+  return (RET_OKAY);
 } /* int do_listval */
 
-static int do_check_con_none (size_t values_num,
-		double *values, char **values_names)
-{
-	int num_critical = 0;
-	int num_warning  = 0;
-	int num_okay = 0;
-	const char *status_str = "UNKNOWN";
-	int status_code = RET_UNKNOWN;
-
-	for (size_t i = 0; i < values_num; i++)
-	{
-		if (isnan (values[i]))
-		{
-			if (nan_is_error_g)
-				num_critical++;
-			else
-				num_warning++;
-		}
-		else if (match_range (&range_critical_g, values[i]) != 0)
-			num_critical++;
-		else if (match_range (&range_warning_g, values[i]) != 0)
-			num_warning++;
-		else
-			num_okay++;
-	}
-
-	if ((num_critical == 0) && (num_warning == 0) && (num_okay == 0))
-	{
-		printf ("WARNING: No defined values found\n");
-		return (RET_WARNING);
-	}
-	else if ((num_critical == 0) && (num_warning == 0))
-	{
-		status_str = "OKAY";
-		status_code = RET_OKAY;
-	}
-	else if (num_critical == 0)
-	{
-		status_str = "WARNING";
-		status_code = RET_WARNING;
-	}
-	else
-	{
-		status_str = "CRITICAL";
-		status_code = RET_CRITICAL;
-	}
-
-	printf ("%s: %i critical, %i warning, %i okay", status_str,
-			num_critical, num_warning, num_okay);
-	if (values_num > 0)
-	{
-		printf (" |");
-		for (size_t i = 0; i < values_num; i++)
-			printf (" %s=%f;;;;", values_names[i], values[i]);
-	}
-	printf ("\n");
+static int do_check_con_none(size_t values_num, double *values,
+                             char **values_names) {
+  int num_critical = 0;
+  int num_warning = 0;
+  int num_okay = 0;
+  const char *status_str = "UNKNOWN";
+  int status_code = RET_UNKNOWN;
+
+  for (size_t i = 0; i < values_num; i++) {
+    if (isnan(values[i])) {
+      if (nan_is_error_g)
+        num_critical++;
+      else
+        num_warning++;
+    } else if (match_range(&range_critical_g, values[i]) != 0)
+      num_critical++;
+    else if (match_range(&range_warning_g, values[i]) != 0)
+      num_warning++;
+    else
+      num_okay++;
+  }
+
+  if ((num_critical == 0) && (num_warning == 0) && (num_okay == 0)) {
+    printf("WARNING: No defined values found\n");
+    return (RET_WARNING);
+  } else if ((num_critical == 0) && (num_warning == 0)) {
+    status_str = "OKAY";
+    status_code = RET_OKAY;
+  } else if (num_critical == 0) {
+    status_str = "WARNING";
+    status_code = RET_WARNING;
+  } else {
+    status_str = "CRITICAL";
+    status_code = RET_CRITICAL;
+  }
+
+  printf("%s: %i critical, %i warning, %i okay", status_str, num_critical,
+         num_warning, num_okay);
+  if (values_num > 0) {
+    printf(" |");
+    for (size_t i = 0; i < values_num; i++)
+      printf(" %s=%f;;;;", values_names[i], values[i]);
+  }
+  printf("\n");
 
-	return (status_code);
+  return (status_code);
 } /* int do_check_con_none */
 
-static int do_check_con_average (size_t values_num,
-		double *values, char **values_names)
-{
-	double total;
-	int total_num;
-	double average;
-	const char *status_str = "UNKNOWN";
-	int status_code = RET_UNKNOWN;
-
-	total = 0.0;
-	total_num = 0;
-	for (size_t i = 0; i < values_num; i++)
-	{
-		if (isnan (values[i]))
-		{
-			if (!nan_is_error_g)
-				continue;
-
-			printf ("CRITICAL: Data source \"%s\" is NaN\n",
-					values_names[i]);
-			return (RET_CRITICAL);
-		}
-
-		total += values[i];
-		total_num++;
-	}
-
-	if (total_num == 0)
-	{
-		printf ("WARNING: No defined values found\n");
-		return (RET_WARNING);
-	}
-
-	average = total / total_num;
-
-	if (match_range (&range_critical_g, average) != 0)
-	{
-		status_str = "CRITICAL";
-		status_code = RET_CRITICAL;
-	}
-	else if (match_range (&range_warning_g, average) != 0)
-	{
-		status_str = "WARNING";
-		status_code = RET_WARNING;
-	}
-	else
-	{
-		status_str = "OKAY";
-		status_code = RET_OKAY;
-	}
-
-	printf ("%s: %g average |", status_str, average);
-	for (size_t i = 0; i < values_num; i++)
-		printf (" %s=%f;;;;", values_names[i], values[i]);
-	printf ("\n");
+static int do_check_con_average(size_t values_num, double *values,
+                                char **values_names) {
+  double total;
+  int total_num;
+  double average;
+  const char *status_str = "UNKNOWN";
+  int status_code = RET_UNKNOWN;
+
+  total = 0.0;
+  total_num = 0;
+  for (size_t i = 0; i < values_num; i++) {
+    if (isnan(values[i])) {
+      if (!nan_is_error_g)
+        continue;
+
+      printf("CRITICAL: Data source \"%s\" is NaN\n", values_names[i]);
+      return (RET_CRITICAL);
+    }
+
+    total += values[i];
+    total_num++;
+  }
+
+  if (total_num == 0) {
+    printf("WARNING: No defined values found\n");
+    return (RET_WARNING);
+  }
+
+  average = total / total_num;
+
+  if (match_range(&range_critical_g, average) != 0) {
+    status_str = "CRITICAL";
+    status_code = RET_CRITICAL;
+  } else if (match_range(&range_warning_g, average) != 0) {
+    status_str = "WARNING";
+    status_code = RET_WARNING;
+  } else {
+    status_str = "OKAY";
+    status_code = RET_OKAY;
+  }
+
+  printf("%s: %g average |", status_str, average);
+  for (size_t i = 0; i < values_num; i++)
+    printf(" %s=%f;;;;", values_names[i], values[i]);
+  printf("\n");
 
-	return (status_code);
+  return (status_code);
 } /* int do_check_con_average */
 
-static int do_check_con_sum (size_t values_num,
-		double *values, char **values_names)
-{
-	double total;
-	int total_num;
-	const char *status_str = "UNKNOWN";
-	int status_code = RET_UNKNOWN;
-
-	total = 0.0;
-	total_num = 0;
-	for (size_t i = 0; i < values_num; i++)
-	{
-		if (isnan (values[i]))
-		{
-			if (!nan_is_error_g)
-				continue;
-
-			printf ("CRITICAL: Data source \"%s\" is NaN\n",
-					values_names[i]);
-			return (RET_CRITICAL);
-		}
-
-		total += values[i];
-		total_num++;
-	}
-
-	if (total_num == 0)
-	{
-		printf ("WARNING: No defined values found\n");
-		return (RET_WARNING);
-	}
-
-	if (match_range (&range_critical_g, total) != 0)
-	{
-		status_str = "CRITICAL";
-		status_code = RET_CRITICAL;
-	}
-	else if (match_range (&range_warning_g, total) != 0)
-	{
-		status_str = "WARNING";
-		status_code = RET_WARNING;
-	}
-	else
-	{
-		status_str = "OKAY";
-		status_code = RET_OKAY;
-	}
-
-	printf ("%s: %g sum |", status_str, total);
-	for (size_t i = 0; i < values_num; i++)
-		printf (" %s=%f;;;;", values_names[i], values[i]);
-	printf ("\n");
+static int do_check_con_sum(size_t values_num, double *values,
+                            char **values_names) {
+  double total;
+  int total_num;
+  const char *status_str = "UNKNOWN";
+  int status_code = RET_UNKNOWN;
+
+  total = 0.0;
+  total_num = 0;
+  for (size_t i = 0; i < values_num; i++) {
+    if (isnan(values[i])) {
+      if (!nan_is_error_g)
+        continue;
+
+      printf("CRITICAL: Data source \"%s\" is NaN\n", values_names[i]);
+      return (RET_CRITICAL);
+    }
+
+    total += values[i];
+    total_num++;
+  }
+
+  if (total_num == 0) {
+    printf("WARNING: No defined values found\n");
+    return (RET_WARNING);
+  }
+
+  if (match_range(&range_critical_g, total) != 0) {
+    status_str = "CRITICAL";
+    status_code = RET_CRITICAL;
+  } else if (match_range(&range_warning_g, total) != 0) {
+    status_str = "WARNING";
+    status_code = RET_WARNING;
+  } else {
+    status_str = "OKAY";
+    status_code = RET_OKAY;
+  }
+
+  printf("%s: %g sum |", status_str, total);
+  for (size_t i = 0; i < values_num; i++)
+    printf(" %s=%f;;;;", values_names[i], values[i]);
+  printf("\n");
 
-	return (status_code);
+  return (status_code);
 } /* int do_check_con_sum */
 
-static int do_check_con_percentage (size_t values_num,
-		double *values, char **values_names)
-{
-	double sum = 0.0;
-	double percentage;
-
-	const char *status_str  = "UNKNOWN";
-	int         status_code = RET_UNKNOWN;
-
-	if ((values_num < 1) || (isnan (values[0])))
-	{
-		printf ("WARNING: The first value is not defined\n");
-		return (RET_WARNING);
-	}
-
-	for (size_t i = 0; i < values_num; i++)
-	{
-		if (isnan (values[i]))
-		{
-			if (!nan_is_error_g)
-				continue;
-
-			printf ("CRITICAL: Data source \"%s\" is NaN\n",
-					values_names[i]);
-			return (RET_CRITICAL);
-		}
-
-		sum += values[i];
-	}
-
-	if (sum == 0.0)
-	{
-		printf ("WARNING: Values sum up to zero\n");
-		return (RET_WARNING);
-	}
-
-	percentage = 100.0 * values[0] / sum;
-
-	if (match_range (&range_critical_g, percentage) != 0)
-	{
-		status_str  = "CRITICAL";
-		status_code = RET_CRITICAL;
-	}
-	else if (match_range (&range_warning_g, percentage) != 0)
-	{
-		status_str  = "WARNING";
-		status_code = RET_WARNING;
-	}
-	else
-	{
-		status_str  = "OKAY";
-		status_code = RET_OKAY;
-	}
-
-	printf ("%s: %lf percent |", status_str, percentage);
-	for (size_t i = 0; i < values_num; i++)
-		printf (" %s=%lf;;;;", values_names[i], values[i]);
-	return (status_code);
+static int do_check_con_percentage(size_t values_num, double *values,
+                                   char **values_names) {
+  double sum = 0.0;
+  double percentage;
+
+  const char *status_str = "UNKNOWN";
+  int status_code = RET_UNKNOWN;
+
+  if ((values_num < 1) || (isnan(values[0]))) {
+    printf("WARNING: The first value is not defined\n");
+    return (RET_WARNING);
+  }
+
+  for (size_t i = 0; i < values_num; i++) {
+    if (isnan(values[i])) {
+      if (!nan_is_error_g)
+        continue;
+
+      printf("CRITICAL: Data source \"%s\" is NaN\n", values_names[i]);
+      return (RET_CRITICAL);
+    }
+
+    sum += values[i];
+  }
+
+  if (sum == 0.0) {
+    printf("WARNING: Values sum up to zero\n");
+    return (RET_WARNING);
+  }
+
+  percentage = 100.0 * values[0] / sum;
+
+  if (match_range(&range_critical_g, percentage) != 0) {
+    status_str = "CRITICAL";
+    status_code = RET_CRITICAL;
+  } else if (match_range(&range_warning_g, percentage) != 0) {
+    status_str = "WARNING";
+    status_code = RET_WARNING;
+  } else {
+    status_str = "OKAY";
+    status_code = RET_OKAY;
+  }
+
+  printf("%s: %lf percent |", status_str, percentage);
+  for (size_t i = 0; i < values_num; i++)
+    printf(" %s=%lf;;;;", values_names[i], values[i]);
+  return (status_code);
 } /* int do_check_con_percentage */
 
-static int do_check (lcc_connection_t *connection)
-{
-	gauge_t *values;
-	char   **values_names;
-	size_t   values_num;
-	char ident_str[1024];
-	lcc_identifier_t ident;
-	int status;
-
-	snprintf (ident_str, sizeof (ident_str), "%s/%s",
-			hostname_g, value_string_g);
-	ident_str[sizeof (ident_str) - 1] = 0;
-
-	status = lcc_string_to_identifier (connection, &ident, ident_str);
-	if (status != 0)
-	{
-		printf ("ERROR: Creating an identifier failed: %s.\n",
-				lcc_strerror (connection));
-		LCC_DESTROY (connection);
-		return (RET_CRITICAL);
-	}
-
-	status = lcc_getval (connection, &ident,
-			&values_num, &values, &values_names);
-	if (status != 0)
-	{
-		printf ("ERROR: Retrieving values from the daemon failed: %s.\n",
-				lcc_strerror (connection));
-		LCC_DESTROY (connection);
-		return (RET_CRITICAL);
-	}
-
-	LCC_DESTROY (connection);
-
-	status = filter_ds (&values_num, &values, &values_names);
-	if (status != RET_OKAY)
-		return (status);
-
-	status = RET_UNKNOWN;
-	if (consolitation_g == CON_NONE)
-		status = do_check_con_none (values_num, values, values_names);
-	else if (consolitation_g == CON_AVERAGE)
-		status = do_check_con_average (values_num, values, values_names);
-	else if (consolitation_g == CON_SUM)
-		status = do_check_con_sum (values_num, values, values_names);
-	else if (consolitation_g == CON_PERCENTAGE)
-		status = do_check_con_percentage (values_num, values, values_names);
-
-	free (values);
-	if (values_names != NULL)
-		for (size_t i = 0; i < values_num; i++)
-			free (values_names[i]);
-	free (values_names);
+static int do_check(lcc_connection_t *connection) {
+  gauge_t *values;
+  char **values_names;
+  size_t values_num;
+  char ident_str[1024];
+  lcc_identifier_t ident;
+  int status;
+
+  snprintf(ident_str, sizeof(ident_str), "%s/%s", hostname_g, value_string_g);
+  ident_str[sizeof(ident_str) - 1] = 0;
+
+  status = lcc_string_to_identifier(connection, &ident, ident_str);
+  if (status != 0) {
+    printf("ERROR: Creating an identifier failed: %s.\n",
+           lcc_strerror(connection));
+    LCC_DESTROY(connection);
+    return (RET_CRITICAL);
+  }
+
+  status = lcc_getval(connection, &ident, &values_num, &values, &values_names);
+  if (status != 0) {
+    printf("ERROR: Retrieving values from the daemon failed: %s.\n",
+           lcc_strerror(connection));
+    LCC_DESTROY(connection);
+    return (RET_CRITICAL);
+  }
+
+  LCC_DESTROY(connection);
+
+  status = filter_ds(&values_num, &values, &values_names);
+  if (status != RET_OKAY)
+    return (status);
+
+  status = RET_UNKNOWN;
+  if (consolitation_g == CON_NONE)
+    status = do_check_con_none(values_num, values, values_names);
+  else if (consolitation_g == CON_AVERAGE)
+    status = do_check_con_average(values_num, values, values_names);
+  else if (consolitation_g == CON_SUM)
+    status = do_check_con_sum(values_num, values, values_names);
+  else if (consolitation_g == CON_PERCENTAGE)
+    status = do_check_con_percentage(values_num, values, values_names);
+
+  free(values);
+  if (values_names != NULL)
+    for (size_t i = 0; i < values_num; i++)
+      free(values_names[i]);
+  free(values_names);
 
-	return (status);
+  return (status);
 } /* int do_check */
 
-int main (int argc, char **argv)
-{
-	char address[1024];
-	lcc_connection_t *connection;
-
-	int status;
-
-	range_critical_g.min = NAN;
-	range_critical_g.max = NAN;
-	range_critical_g.invert = 0;
-
-	range_warning_g.min = NAN;
-	range_warning_g.max = NAN;
-	range_warning_g.invert = 0;
-
-	while (42)
-	{
-		int c;
-
-		c = getopt (argc, argv, "w:c:s:n:H:g:d:hm");
-		if (c < 0)
-			break;
-
-		switch (c)
-		{
-			case 'c':
-				parse_range (optarg, &range_critical_g);
-				break;
-			case 'w':
-				parse_range (optarg, &range_warning_g);
-				break;
-			case 's':
-				socket_file_g = optarg;
-				break;
-			case 'n':
-				value_string_g = optarg;
-				break;
-			case 'H':
-				hostname_g = optarg;
-				break;
-			case 'g':
-				if (strcasecmp (optarg, "none") == 0)
-					consolitation_g = CON_NONE;
-				else if (strcasecmp (optarg, "average") == 0)
-					consolitation_g = CON_AVERAGE;
-				else if (strcasecmp (optarg, "sum") == 0)
-					consolitation_g = CON_SUM;
-				else if (strcasecmp (optarg, "percentage") == 0)
-					consolitation_g = CON_PERCENTAGE;
-				else
-				{
-					fprintf (stderr, "Unknown consolidation function `%s'.\n",
-							optarg);
-					usage (argv[0]);
-				}
-				break;
-			case 'd':
-			{
-				char **tmp;
-				tmp = realloc (match_ds_g,
-						(match_ds_num_g + 1)
-						* sizeof (char *));
-				if (tmp == NULL)
-				{
-					fprintf (stderr, "realloc failed: %s\n",
-							strerror (errno));
-					return (RET_UNKNOWN);
-				}
-				match_ds_g = tmp;
-				match_ds_g[match_ds_num_g] = cn_strdup (optarg);
-				if (match_ds_g[match_ds_num_g] == NULL)
-				{
-					fprintf (stderr, "cn_strdup failed: %s\n",
-							strerror (errno));
-					return (RET_UNKNOWN);
-				}
-				match_ds_num_g++;
-				break;
-			}
-			case 'm':
-				nan_is_error_g = 1;
-				break;
-			default:
-				usage (argv[0]);
-		} /* switch (c) */
-	}
-
-	if ((socket_file_g == NULL) || (value_string_g == NULL)
-			|| ((hostname_g == NULL) && (strcasecmp (value_string_g, "LIST"))))
-	{
-		fprintf (stderr, "Missing required arguments.\n");
-		usage (argv[0]);
-	}
-
-	snprintf (address, sizeof (address), "unix:%s", socket_file_g);
-	address[sizeof (address) - 1] = 0;
-
-	connection = NULL;
-	status = lcc_connect (address, &connection);
-	if (status != 0)
-	{
-		printf ("ERROR: Connecting to daemon at %s failed.\n",
-				socket_file_g);
-		return (RET_CRITICAL);
-	}
+int main(int argc, char **argv) {
+  char address[1024];
+  lcc_connection_t *connection;
+
+  int status;
+
+  range_critical_g.min = NAN;
+  range_critical_g.max = NAN;
+  range_critical_g.invert = 0;
+
+  range_warning_g.min = NAN;
+  range_warning_g.max = NAN;
+  range_warning_g.invert = 0;
+
+  while (42) {
+    int c;
+
+    c = getopt(argc, argv, "w:c:s:n:H:g:d:hm");
+    if (c < 0)
+      break;
+
+    switch (c) {
+    case 'c':
+      parse_range(optarg, &range_critical_g);
+      break;
+    case 'w':
+      parse_range(optarg, &range_warning_g);
+      break;
+    case 's':
+      socket_file_g = optarg;
+      break;
+    case 'n':
+      value_string_g = optarg;
+      break;
+    case 'H':
+      hostname_g = optarg;
+      break;
+    case 'g':
+      if (strcasecmp(optarg, "none") == 0)
+        consolitation_g = CON_NONE;
+      else if (strcasecmp(optarg, "average") == 0)
+        consolitation_g = CON_AVERAGE;
+      else if (strcasecmp(optarg, "sum") == 0)
+        consolitation_g = CON_SUM;
+      else if (strcasecmp(optarg, "percentage") == 0)
+        consolitation_g = CON_PERCENTAGE;
+      else {
+        fprintf(stderr, "Unknown consolidation function `%s'.\n", optarg);
+        usage(argv[0]);
+      }
+      break;
+    case 'd': {
+      char **tmp;
+      tmp = realloc(match_ds_g, (match_ds_num_g + 1) * sizeof(char *));
+      if (tmp == NULL) {
+        fprintf(stderr, "realloc failed: %s\n", strerror(errno));
+        return (RET_UNKNOWN);
+      }
+      match_ds_g = tmp;
+      match_ds_g[match_ds_num_g] = cn_strdup(optarg);
+      if (match_ds_g[match_ds_num_g] == NULL) {
+        fprintf(stderr, "cn_strdup failed: %s\n", strerror(errno));
+        return (RET_UNKNOWN);
+      }
+      match_ds_num_g++;
+      break;
+    }
+    case 'm':
+      nan_is_error_g = 1;
+      break;
+    default:
+      usage(argv[0]);
+    } /* switch (c) */
+  }
+
+  if ((socket_file_g == NULL) || (value_string_g == NULL) ||
+      ((hostname_g == NULL) && (strcasecmp(value_string_g, "LIST")))) {
+    fprintf(stderr, "Missing required arguments.\n");
+    usage(argv[0]);
+  }
+
+  snprintf(address, sizeof(address), "unix:%s", socket_file_g);
+  address[sizeof(address) - 1] = 0;
+
+  connection = NULL;
+  status = lcc_connect(address, &connection);
+  if (status != 0) {
+    printf("ERROR: Connecting to daemon at %s failed.\n", socket_file_g);
+    return (RET_CRITICAL);
+  }
 
-	if (0 == strcasecmp (value_string_g, "LIST"))
-		return (do_listval (connection));
+  if (0 == strcasecmp(value_string_g, "LIST"))
+    return (do_listval(connection));
 
-	return (do_check (connection));
+  return (do_check(connection));
 } /* int main */
