void
QosConfig::dumpConfigLine(char *entry, const char *name) const
{
    char *p = entry;
    snprintf(p, 10, "%s", name); // strlen("qos_flows ");
    p += strlen(name);

    if (tos_local_hit >0) {
        snprintf(p, 15, " local-hit=%2x", tos_local_hit);
        p += 15;
    }

    if (tos_sibling_hit >0) {
        snprintf(p, 17, " sibling-hit=%2x", tos_sibling_hit);
        p += 17;
    }
    if (tos_parent_hit >0) {
        snprintf(p, 16, " parent-hit=%2x", tos_parent_hit);
        p += 16;
    }
    if (preserve_miss_tos != 0) {
        snprintf(p, 22, " disable-preserve-miss");
        p += 22;
    }
    if (preserve_miss_tos && preserve_miss_tos_mask != 0) {
        snprintf(p, 15, " miss-mask=%2x", preserve_miss_tos_mask);
        p += 15;
    }
    snprintf(p, 1, "\n");
//    p += 1;
}