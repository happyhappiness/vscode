  *   Florian octo Forster <octo at verplant.org>
  *   Alvaro Barcellos <alvaro.barcellos at gmail.com>
  **/
 
 #include "collectd.h"
 #include "common.h"
-#include "utils_debug.h"
 
-#include "network.h"
 #include "plugin.h"
 #include "configfile.h"
+#include "types_list.h"
 
-static int loop = 0;
-
+/*
+ * Global variables
+ */
+char hostname_g[DATA_MAX_NAME_LEN];
+int  interval_g;
 #if HAVE_LIBKSTAT
 kstat_ctl_t *kc;
 #endif /* HAVE_LIBKSTAT */
 
-/*
- * exported variables
- */
-time_t curtime;
-int    operating_mode;
+static int loop = 0;
 
 static void sigIntHandler (int signal)
 {
 	loop++;
 }
 
 static void sigTermHandler (int signal)
 {
 	loop++;
 }
 
-static int change_basedir (char *dir)
+static int init_global_variables (void)
+{
+	const char *str;
+
+	str = global_option_get ("Hostname");
+	if (str != NULL)
+	{
+		strncpy (hostname_g, str, sizeof (hostname_g));
+	}
+	else
+	{
+		if (gethostname (hostname_g, sizeof (hostname_g)) != 0)
+		{
+			fprintf (stderr, "`gethostname' failed and no "
+					"hostname was configured.\n");
+			return (-1);
+		}
+	}
+	DEBUG ("hostname_g = %s;", hostname_g);
+
+	str = global_option_get ("Interval");
+	if (str == NULL)
+		str = "10";
+	interval_g = atoi (str);
+	if (interval_g <= 0)
+	{
+		fprintf (stderr, "Cannot set the interval to a correct value.\n"
+				"Please check your settings.\n");
+		return (-1);
+	}
+	DEBUG ("interval_g = %i;", interval_g);
+
+	return (0);
+} /* int init_global_variables */
+
+static int change_basedir (const char *orig_dir)
 {
-	int dirlen = strlen (dir);
+	char *dir = strdup (orig_dir);
+	int dirlen;
+	int status;
+
+	if (dir == NULL)
+	{
+		char errbuf[1024];
+		ERROR ("strdup failed: %s",
+				sstrerror (errno, errbuf, sizeof (errbuf)));
+		return (-1);
+	}
 	
+	dirlen = strlen (dir);
 	while ((dirlen > 0) && (dir[dirlen - 1] == '/'))
 		dir[--dirlen] = '\0';
 
 	if (dirlen <= 0)
 		return (-1);
 
-	if (chdir (dir) == -1)
+	status = chdir (dir);
+	free (dir);
+
+	if (status != 0)
 	{
 		if (errno == ENOENT)
 		{
-			if (mkdir (dir, 0755) == -1)
+			if (mkdir (orig_dir, 0755) == -1)
 			{
-				syslog (LOG_ERR, "mkdir (%s): %s", dir, strerror (errno));
+				char errbuf[1024];
+				ERROR ("mkdir (%s): %s", orig_dir,
+						sstrerror (errno, errbuf,
+							sizeof (errbuf)));
 				return (-1);
 			}
-			else if (chdir (dir) == -1)
+			else if (chdir (orig_dir) == -1)
 			{
-				syslog (LOG_ERR, "chdir (%s): %s", dir, strerror (errno));
+				char errbuf[1024];
+				ERROR ("chdir (%s): %s", orig_dir,
+						sstrerror (errno, errbuf,
+							sizeof (errbuf)));
 				return (-1);
 			}
 		}
 		else
 		{
-			syslog (LOG_ERR, "chdir: %s", strerror (errno));
+			char errbuf[1024];
+			ERROR ("chdir (%s): %s", orig_dir,
+					sstrerror (errno, errbuf,
+						sizeof (errbuf)));
 			return (-1);
 		}
 	}
 
 	return (0);
 } /* static int change_basedir (char *dir) */
