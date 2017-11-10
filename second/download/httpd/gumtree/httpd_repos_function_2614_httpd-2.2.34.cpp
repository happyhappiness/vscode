static void spawn_child(int slot)
{
    PPIB ppib;
    PTIB ptib;
    char fail_module[100];
    char progname[CCHMAXPATH];
    RESULTCODES proc_rc;
    ULONG rc;

    ap_scoreboard_image->parent[slot].generation = ap_my_generation;
    DosGetInfoBlocks(&ptib, &ppib);
    DosQueryModuleName(ppib->pib_hmte, sizeof(progname), progname);
    rc = DosExecPgm(fail_module, sizeof(fail_module), EXEC_ASYNCRESULT,
                    ppib->pib_pchcmd, NULL, &proc_rc, progname);

    if (rc) {
        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
                     "error spawning child, slot %d", slot);
    }

    if (ap_max_daemons_limit < slot) {
        ap_max_daemons_limit = slot;
    }

    ap_scoreboard_image->parent[slot].pid = proc_rc.codeTerminate;
}