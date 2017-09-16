    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {

        return err;

    }



    ap_threads_per_child = atoi(arg);

#ifdef WIN32

    if (ap_threads_per_child > 64) {

	return "Can't have more than 64 threads in Windows (for now)";

    }

#endif



    return NULL;

}



static const char *set_excess_requests(cmd_parms *cmd, void *dummy, char *arg) 

{

