

#ifdef _OSD_POSIX

#include "httpd.h"

#include "http_config.h"

#include "http_log.h"



static const char *bs2000_authfile = NULL;





/* This routine is called by http_core for the BS2000AuthFile directive */

/* It stores the file name (after a quick check for validity) for later use */

const char *os_set_authfile(pool *p, const char *name)

{

    struct stat stbuf;

    char *filename;



    filename = ap_server_root_relative(p, name);



    /* auth file must exist */

    if (stat(filename, &stbuf) != 0) {

	return ap_pstrcat(p, "Unable to access bs2000 auth file ",

		       filename, NULL);

	exit(APEXIT_CHILDFATAL);

    }



    /* auth file must be owned by root, and not readable/writable by everyone else */

    if (stbuf.st_uid != 0) {

	return ap_pstrcat(p, "BS2000 auth file ", filename,

		       " is not owned by SYSROOT - "

		       "change owner!", NULL);

    }



    if (stbuf.st_mode & (S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) {

	return ap_pstrcat(p, "BS2000 auth file ", filename,

		       " is readable/writable by others - "

		       "check permissions!", NULL);

    }



    bs2000_authfile = filename;

    return NULL;

}



int os_init_job_environment(server_rec *server, const char *user_name)

{

    _checkuser_struct       chk_usr;

    _rini_struct            inittask; 

    struct {

	char username[8+1];     /* Length of a user name including \0 */

	char password[8+1];     /* Length of a password including \0 */

	char account [8+1];     /* Length of a account number including \0 */

	char exp_date[10+1];    /* Length of a date including \0 */

	char exp_pass[10+1];    /* Length of a date including \0 */

	char processor[8+1];

    } lcl_data;

    char *cp;

    FILE *pwfile;

    struct stat stbuf;



    memset (&lcl_data, '\0', sizeof lcl_data);



    /* BS2000 requires the user name to be in upper case for authentication */

    ap_snprintf(lcl_data.username, sizeof lcl_data.username,

		"%s", user_name);

    for (cp = lcl_data.username; *cp; ++cp) {

	*cp = ap_toupper(*cp);

    }



    if (bs2000_authfile == NULL) {

	ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO, server,

		     "Use the 'BS2000AuthFile <passwdfile>' directive to specify "

		     "an authorization file for User %s",

		     user_name);

	exit(APEXIT_CHILDFATAL);

    }



    if ((pwfile = fopen(bs2000_authfile, "r")) == NULL) {

	ap_log_error(APLOG_MARK, APLOG_ALERT, server,

		     "Unable to open bs2000 auth file %s for User %s",

		     bs2000_authfile, user_name);

	exit(APEXIT_CHILDFATAL);

    }



    if (fgets(lcl_data.password, sizeof lcl_data.password, pwfile) == NULL

	|| strlen(lcl_data.password) == 0) {

	ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO, server,

		     "Unable ro read BS2000 auth file %s",

		     bs2000_authfile);

	exit(APEXIT_CHILDFATAL);

    }



    fclose(pwfile);



    chk_usr.username      = lcl_data.username;

    chk_usr.password      = lcl_data.password;

    chk_usr.account       = lcl_data.account; /* Account and Expiration go here*/

    chk_usr.logon_expdate = lcl_data.exp_date;

    chk_usr.pw_expdate    = lcl_data.exp_pass;



    /* Now perform validity check of user and password, filling in account */

    if(_checkuser(&chk_usr) != 0) {

	ap_log_error(APLOG_MARK, APLOG_ALERT, server,

		     "_checkuser: BS2000 auth failed for user %s", chk_usr.username);

	exit(APEXIT_CHILDFATAL);

    }



    inittask.username = chk_usr.username;

    inittask.account  = chk_usr.account;

    inittask.processor_name = strncpy(lcl_data.processor,

				      "        ",

				      sizeof lcl_data.processor);



    /* And switch to the new logon user (setuid() and setgid() are done later) */

    if (_rini(&inittask) != 0) {

	ap_log_error(APLOG_MARK, APLOG_ALERT, server,

		     "_rini: BS2000 auth failed for user %s",

		     inittask.username);

	exit(APEXIT_CHILDFATAL);

    }



    /*ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, server,

		     "BS2000 logon for user %s account=%s completed, pid=%d.",

		     inittask.username, inittask.account, getpid());*/



    /* Don't leave the password on the stack */

    memset (&lcl_data, '\0', sizeof lcl_data);



    return 0;

}



#else /* _OSD_POSIX */

void bs2login_is_not_here()

{

-- apache_1.3.1/src/os/bs2000/os.c	1998-05-08 17:51:54.000000000 +0800

