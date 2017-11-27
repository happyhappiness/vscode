 *   Florian octo Forster <octo at verplant.org>
 *   Alvaro Barcellos <alvaro.barcellos at gmail.com>
 **/

#include "collectd.h"
#include "common.h"
#include "utils_debug.h"

#include "network.h"
#include "plugin.h"
#include "configfile.h"

static int loop = 0;

#if HAVE_LIBKSTAT
kstat_ctl_t *kc;
#endif /* HAVE_LIBKSTAT */

/*
 * exported variables
 */
time_t curtime;
int    operating_mode;

static void sigIntHandler (int signal)
{
	loop++;
}

static void sigTermHandler (int signal)
{
	loop++;
}

static int change_basedir (char *dir)
{
	int dirlen = strlen (dir);
	
	while ((dirlen > 0) && (dir[dirlen - 1] == '/'))
		dir[--dirlen] = '\0';

	if (dirlen <= 0)
		return (-1);

	if (chdir (dir) == -1)
	{
		if (errno == ENOENT)
		{
			if (mkdir (dir, 0755) == -1)
			{
				syslog (LOG_ERR, "mkdir (%s): %s", dir, strerror (errno));
				return (-1);
			}
			else if (chdir (dir) == -1)
			{
				syslog (LOG_ERR, "chdir (%s): %s", dir, strerror (errno));
				return (-1);
			}
		}
		else
		{
			syslog (LOG_ERR, "chdir: %s", strerror (errno));
			return (-1);
		}
	}

	return (0);
} /* static int change_basedir (char *dir) */
