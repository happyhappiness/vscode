static const char *cmd_hm_maxworkers(cmd_parms *cmd,
                                  void *dconf, const char *data)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    maxworkers = atoi(data);
    if (maxworkers <= 10)
        return "HeartbeatMaxServers: Should be bigger than 10";

    return NULL;
}