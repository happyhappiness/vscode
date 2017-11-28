void
parse_wccp2_service(void *v)
{
    char *t;
    int service = 0;
    int service_id = 0;
    int security_type = WCCP2_NO_SECURITY;
    char wccp_password[WCCP2_PASSWORD_LEN + 1];

    if (wccp2_connected == 1) {
        debugs(80, 1, "WCCPv2: Somehow reparsing the configuration without having shut down WCCP! Try reloading squid again.");
        return;
    }

    /* Snarf the type */
    if ((t = strtok(NULL, w_space)) == NULL) {
        debugs(80, 0, "wccp2ParseServiceInfo: missing service info type (standard|dynamic)");
        self_destruct();
    }

    if (strcmp(t, "standard") == 0) {
        service = WCCP2_SERVICE_STANDARD;
    } else if (strcmp(t, "dynamic") == 0) {
        service = WCCP2_SERVICE_DYNAMIC;
    } else {
        debugs(80, 0, "wccp2ParseServiceInfo: bad service info type (expected standard|dynamic, got " << t << ")");
        self_destruct();
    }

    /* Snarf the ID */
    service_id = GetInteger();

    if (service_id < 0 || service_id > 255) {
        debugs(80, 0, "wccp2ParseServiceInfo: service info id " << service_id << " is out of range (0..255)");
        self_destruct();
    }

    memset(wccp_password, 0, sizeof(wccp_password));
    /* Handle password, if any */

    if ((t = strtok(NULL, w_space)) != NULL) {
        if (strncmp(t, "password=", 9) == 0) {
            security_type = WCCP2_MD5_SECURITY;
            strncpy(wccp_password, t + 9, WCCP2_PASSWORD_LEN);
        }
    }

    /* Create a placeholder service record */
    wccp2_add_service_list(service, service_id, 0, 0, 0, empty_portlist, security_type, wccp_password);
}