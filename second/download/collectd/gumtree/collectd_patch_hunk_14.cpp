 				apcups_detail->outputv = value;
 			else if (strcmp ("LINEFREQ", key) == 0)
 				apcups_detail->linefreq = value;
 			else if (strcmp ("TIMELEFT", key) == 0)
 				apcups_detail->timeleft = value;
 
-			tokptr = strtok (NULL, ":");
+			tokptr = strtok_r (NULL, ":", &toksaveptr);
 		} /* while (tokptr != NULL) */
 	}
 	
 	if (n < 0)
 	{
-		syslog (LOG_WARNING, "apcups plugin: Error reading from socket");
+		WARNING ("apcups plugin: Error reading from socket");
 		return (-1);
 	}
-#if APCMAIN
-	else
-	{
-		/* close the opened socket */
-		net_close (&sockfd);
-	}
-#endif /* APCMAIN */
 
 	return (0);
 }
 
-#if APCMAIN
-/*
- * This is used for testing apcups in a standalone mode.
- * Usefull for debugging.
- */
-int main (int argc, char **argv)
-{
-	/* we are not really going to use this */
-	struct apc_detail_s apcups_detail;
-
-	openlog ("apcups", LOG_PID | LOG_NDELAY | LOG_LOCAL1, LOG_USER);
-
-	if (global_host == NULL || strcmp (global_host, "0.0.0.0") == 0)
-		global_host = "localhost";
-
-	if(apc_query_server (global_host, global_port, &apcups_detail) < 0)
-	{
-		printf("apcups: Failed...\n");
-		return(-1);
-	}
-
-	return 0;
-}
-#else
-static int apcups_config (char *key, char *value)
+static int apcups_config (const char *key, const char *value)
 {
 	if (strcasecmp (key, "host") == 0)
 	{
-		if (global_host != NULL)
+		if (conf_host != NULL)
 		{
-			free (global_host);
-			global_host = NULL;
+			free (conf_host);
+			conf_host = NULL;
 		}
-		if ((global_host = strdup (value)) == NULL)
+		if ((conf_host = strdup (value)) == NULL)
 			return (1);
 	}
 	else if (strcasecmp (key, "Port") == 0)
 	{
 		int port_tmp = atoi (value);
 		if (port_tmp < 1 || port_tmp > 65535)
 		{
-			syslog (LOG_WARNING, "apcups plugin: Invalid port: %i", port_tmp);
+			WARNING ("apcups plugin: Invalid port: %i", port_tmp);
 			return (1);
 		}
-		global_port = port_tmp;
+		conf_port = port_tmp;
 	}
 	else
 	{
 		return (-1);
 	}
 	return (0);
 }
 
-static void apcups_init (void)
-{
-	return;
-}
-
-static void apc_write_voltage (char *host, char *inst, char *val)
-{
-	char file[512];
-	int  status;
-
-	status = snprintf (file, 512, bvolt_file_template, inst);
-	if ((status < 1) || (status >= 512))
-		return;
-
-	rrd_update_file (host, file, val, bvolt_ds_def, bvolt_ds_num);
-}
-
-static void apc_write_charge (char *host, char *inst, char *val)
-{
-	rrd_update_file (host, charge_file_template, val, charge_ds_def, charge_ds_num);
-}
-
-static void apc_write_percent (char *host, char *inst, char *val)
-{
-	rrd_update_file (host, load_file_template, val, load_ds_def, load_ds_num);
-}
-
-static void apc_write_timeleft (char *host, char *inst, char *val)
-{
-	rrd_update_file (host, time_file_template, val, time_ds_def, time_ds_num);
-}
-
-static void apc_write_temperature (char *host, char *inst, char *val)
-{
-	rrd_update_file (host, temp_file_template, val, temp_ds_def, temp_ds_num);
-}
-
-static void apc_write_frequency (char *host, char *inst, char *val)
+static void apc_submit_generic (char *type, char *type_inst, double value)
 {
-	char file[512];
-	int  status;
-
-	status = snprintf (file, 512, freq_file_template, inst);
-	if ((status < 1) || (status >= 512))
-		return;
+	value_t values[1];
+	value_list_t vl = VALUE_LIST_INIT;
 
-	rrd_update_file (host, file, val, freq_ds_def, freq_ds_num);
-}
-
-static void apc_submit_generic (char *type, char *inst,
-		double value)
-{
-	char buf[512];
-	int  status;
+	values[0].gauge = value;
 
-	status = snprintf (buf, 512, "%u:%f",
-			(unsigned int) curtime, value);
-	if ((status < 1) || (status >= 512))
-		return;
+	vl.values = values;
+	vl.values_len = 1;
+	vl.time = time (NULL);
+	strcpy (vl.host, hostname_g);
+	strcpy (vl.plugin, "apcups");
+	strcpy (vl.plugin_instance, "");
+	strncpy (vl.type_instance, type_inst, sizeof (vl.type_instance));
 
-	DBG ("plugin_submit (%s, %s, %s);", type, inst, buf);
-	plugin_submit (type, inst, buf);
+	plugin_dispatch_values (type, &vl);
 }
 
 static void apc_submit (struct apc_detail_s *apcups_detail)
 {
 	apc_submit_generic ("apcups_voltage",    "input",   apcups_detail->linev);
 	apc_submit_generic ("apcups_voltage",    "output",  apcups_detail->outputv);
 	apc_submit_generic ("apcups_voltage",    "battery", apcups_detail->battv);
-	apc_submit_generic ("apcups_charge",     "-",       apcups_detail->bcharge);
-	/* `apcups_charge_pct' actually is the wrong name, but we keep it that
-	 * way for backwards compatibility. */
-	apc_submit_generic ("apcups_charge_pct", "-",       apcups_detail->loadpct);
-	apc_submit_generic ("apcups_timeleft",   "-",       apcups_detail->timeleft);
-	apc_submit_generic ("apcups_temp",       "-",       apcups_detail->itemp);
+	apc_submit_generic ("apcups_charge",     "",        apcups_detail->bcharge);
+	apc_submit_generic ("apcups_charge_pct", "",        apcups_detail->loadpct);
+	apc_submit_generic ("apcups_timeleft",   "",        apcups_detail->timeleft);
+	apc_submit_generic ("apcups_temp",       "",        apcups_detail->itemp);
 	apc_submit_generic ("apcups_frequency",  "input",   apcups_detail->linefreq);
 }
 
-static void apcups_read (void)
+static int apcups_read (void)
 {
 	struct apc_detail_s apcups_detail;
 	int status;
 
 	apcups_detail.linev    =   -1.0;
 	apcups_detail.outputv  =   -1.0;
