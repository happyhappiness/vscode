                APR_SIZE_T_FMT " bytes)\n", strlen(s));
        exit(1);
    }
    return ret;
}

/* pool abort function */
static int abort_on_oom(int retcode)
{
    fprintf(stderr, "Could not allocate memory\n");
    exit(1);
    /* not reached */
