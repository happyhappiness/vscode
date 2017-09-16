

#ifdef _OSD_POSIX

#include "httpd.h"

#include "http_config.h"

#include "http_log.h"



static const char *bs2000_account = NULL;





/* This routine is called by http_core for the BS2000Account directive */

/* It stores the account name for later use */

const char *os_set_account(pool *p, const char *account)

{

    if (bs2000_account != NULL && strcasecmp(bs2000_account, account) != 0)

        return "BS2000Account: can be defined only once.";



    bs2000_account = ap_pstrdup(p, account);

    return NULL;

}



int os_init_job_environment(server_rec *server, const char *user_name)

{

    _rini_struct            inittask; 



    /* We can be sure that no change to uid==0 is possible because of

     * the checks in http_core.c:set_user()

     */



    /* An Account is required for _rini() */

    if (bs2000_account == NULL)

    {

	ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO, server,

		     "No BS2000Account configured - cannot switch to User %S",

		     user_name);

	exit(APEXIT_CHILDFATAL);

    }



    inittask.username       = user_name;

    inittask.account        = bs2000_account;

    inittask.processor_name = "        ";



    /* Switch to the new logon user (setuid() and setgid() are done later) */

    /* Only the super use can switch identities. */

    if (_rini(&inittask) != 0) {

	ap_log_error(APLOG_MARK, APLOG_ALERT, server,

		     "_rini: BS2000 auth failed for user \"%s\" acct \"%s\"",

		     inittask.username, inittask.account);

	exit(APEXIT_CHILDFATAL);

    }



    return 0;

}



#else /* _OSD_POSIX */

void bs2login_is_not_here()

{

++ apache_1.3.2/src/os/bs2000/os.c	1998-09-15 00:24:51.000000000 +0800

