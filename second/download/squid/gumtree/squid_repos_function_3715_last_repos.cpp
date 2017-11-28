void icapLogLog(AccessLogEntry::Pointer &al)
{
    if (IcapLogfileStatus == LOG_ENABLE) {
        ACLFilledChecklist checklist(NULL, al->adapted_request, NULL);
        if (al->reply) {
            checklist.reply = al->reply;
            HTTPMSGLOCK(checklist.reply);
        }
        accessLogLogTo(Config.Log.icaplogs, al, &checklist);
    }
}