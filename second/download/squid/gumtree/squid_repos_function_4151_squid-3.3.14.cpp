void Adaptation::Icap::Xaction::maybeLog()
{
    if (IcapLogfileStatus == LOG_ENABLE) {
        ACLFilledChecklist *checklist = new ACLFilledChecklist(::Config.accessList.icap, al.request, dash_str);
        if (al.reply) {
            checklist->reply = al.reply;
            HTTPMSGLOCK(checklist->reply);
        }
        if (!::Config.accessList.icap || checklist->fastCheck() == ACCESS_ALLOWED) {
            finalizeLogInfo();
            icapLogLog(alep, checklist);
        }
        delete checklist;
    }
}