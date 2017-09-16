	version_locked++;

    }

}



static APACHE_TLS int volatile exit_after_unblock = 0;



/* a clean exit from a child with proper cleanup */

static void __attribute__((noreturn)) clean_child_exit(int code)

{

    if (pchild) {

	ap_child_exit_modules(pchild, server_conf);

	ap_destroy_pool(pchild);

    }

    exit(code);

}



#if defined(USE_FCNTL_SERIALIZED_ACCEPT) || defined(USE_FLOCK_SERIALIZED_ACCEPT)

static void expand_lock_fname(pool *p)

{

