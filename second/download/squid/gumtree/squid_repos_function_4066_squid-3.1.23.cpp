void icapLogLog(AccessLogEntry *al, ACLChecklist * checklist)
{
    if (IcapLogfileStatus == LOG_ENABLE)
        accessLogLogTo(Config.Log.icaplogs, al, checklist);
}