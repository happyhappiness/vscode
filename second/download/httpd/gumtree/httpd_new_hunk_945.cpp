	ap_log_error(APLOG_MARK, APLOG_EMERG, server_conf,

		    "flock: LOCK_UN: Error freeing accept lock. Exiting!");

	clean_child_exit(APEXIT_CHILDFATAL);

    }

}



#elif defined(USE_OS2SEM_SERIALIZED_ACCEPT)



static HMTX lock_sem = -1;



static void accept_mutex_cleanup(void *foo)

{

    DosReleaseMutexSem(lock_sem);

    DosCloseMutexSem(lock_sem);

}



/*

 * Initialize mutex lock.

 * Done by each child at it's birth

 */

static void accept_mutex_child_init(pool *p)

{

    int rc = DosOpenMutexSem(NULL, &lock_sem);



    if (rc != 0) {

	ap_log_error(APLOG_MARK, APLOG_EMERG, server_conf,

		    "Child cannot open lock semaphore");

	clean_child_exit(APEXIT_CHILDINIT);

    }

}



/*

 * Initialize mutex lock.

 * Must be safe to call this on a restart.

 */

static void accept_mutex_init(pool *p)

{

    int rc = DosCreateMutexSem(NULL, &lock_sem, DC_SEM_SHARED, FALSE);



    if (rc != 0) {

	ap_log_error(APLOG_MARK, APLOG_EMERG, server_conf,

		    "Parent cannot create lock semaphore");

	exit(APEXIT_INIT);

    }



    ap_register_cleanup(p, NULL, accept_mutex_cleanup, ap_null_cleanup);

}



static void accept_mutex_on(void)

{

    int rc = DosRequestMutexSem(lock_sem, SEM_INDEFINITE_WAIT);



    if (rc != 0) {

	ap_log_error(APLOG_MARK, APLOG_EMERG, server_conf,

		    "OS2SEM: Error %d getting accept lock. Exiting!", rc);

	clean_child_exit(APEXIT_CHILDFATAL);

    }

}



static void accept_mutex_off(void)

{

    int rc = DosReleaseMutexSem(lock_sem);

    

    if (rc != 0) {

	ap_log_error(APLOG_MARK, APLOG_EMERG, server_conf,

		    "OS2SEM: Error %d freeing accept lock. Exiting!", rc);

	clean_child_exit(APEXIT_CHILDFATAL);

    }

}



#else

/* Default --- no serialization.  Other methods *could* go here,

 * as #elifs...

 */

#if !defined(MULTITHREAD)

/* Multithreaded systems don't complete between processes for

