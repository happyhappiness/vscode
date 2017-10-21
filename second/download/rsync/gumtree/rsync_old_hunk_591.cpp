   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/*
  logging and utility functions

  tridge, May 1998
  */
#include "rsync.h"

static FILE *logfile;
static int log_error_fd = -1;

static void logit(int priority, char *buf)
{
	if (logfile) {
		fprintf(logfile,"%s [%d] %s", 
			timestring(time(NULL)), (int)getpid(), buf);
		fflush(logfile);
	} else {
		syslog(priority, "%s", buf);
	}
}

void log_open(void)
{
	static int initialised;
	int options = LOG_PID;
	time_t t;
	char *logf;

	if (initialised) return;
	initialised = 1;

	/* this looks pointless, but it is needed in order for the
	   C library on some systems to fetch the timezone info
	   before the chroot */
	t = time(NULL);
	localtime(&t);

	/* optionally use a log file instead of syslog */
	logf = lp_log_file();
	if (logf && *logf) {
		extern int orig_umask;
		int old_umask = umask(022 | orig_umask);
		logfile = fopen(logf, "a");
		umask(old_umask);
		return;
	}

#ifdef LOG_NDELAY
	options |= LOG_NDELAY;
#endif

