void
Ip::Qos::Config::dumpConfigLine(char *entry, const char *name) const
{
    char *p = entry;
    if (isHitTosActive()) {

        p += snprintf(p, 11, "%s", name); // strlen("qos_flows ");
        p += snprintf(p, 4, "%s", "tos");

        if (tosLocalHit > 0) {
            p += snprintf(p, 16, " local-hit=0x%02X", tosLocalHit);
        }
        if (tosSiblingHit > 0) {
            p += snprintf(p, 18, " sibling-hit=0x%02X", tosSiblingHit);
        }
        if (tosParentHit > 0) {
            p += snprintf(p, 17, " parent-hit=0x%02X", tosParentHit);
        }
        if (tosMiss > 0) {
            p += snprintf(p, 11, " miss=0x%02X", tosMiss);
            if (tosMissMask!=0xFFU) {
                p += snprintf(p, 6, "/0x%02X", tosMissMask);
            }
        }
        if (preserveMissTos == 0) {
            p += snprintf(p, 23, " disable-preserve-miss");
        }
        if (preserveMissTos && preserveMissTosMask != 0) {
            p += snprintf(p, 16, " miss-mask=0x%02X", preserveMissTosMask);
        }
        p += snprintf(p, 2, "\n");
    }

    if (isHitNfmarkActive()) {
        p += snprintf(p, 11, "%s", name); // strlen("qos_flows ");
        p += snprintf(p, 5, "%s", "mark");

        if (markLocalHit > 0) {
            p += snprintf(p, 22, " local-hit=0x%02X", markLocalHit);
        }
        if (markSiblingHit > 0) {
            p += snprintf(p, 24, " sibling-hit=0x%02X", markSiblingHit);
        }
        if (markParentHit > 0) {
            p += snprintf(p, 23, " parent-hit=0x%02X", markParentHit);
        }
        if (markMiss > 0) {
            p += snprintf(p, 17, " miss=0x%02X", markMiss);
            if (markMissMask!=0xFFFFFFFFU) {
                p += snprintf(p, 12, "/0x%02X", markMissMask);
            }
        }
        if (preserveMissMark == false) {
            p += snprintf(p, 23, " disable-preserve-miss");
        }
        if (preserveMissMark && preserveMissMarkMask != 0) {
            p += snprintf(p, 22, " miss-mask=0x%02X", preserveMissMarkMask);
        }
        p += snprintf(p, 2, "\n");
    }
}