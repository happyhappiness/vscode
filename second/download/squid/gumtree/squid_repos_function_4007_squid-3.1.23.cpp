void Adaptation::Icap::Xaction::maybeLog()
{
    if (IcapLogfileStatus == LOG_ENABLE) {
        ACLChecklist *checklist = new ACLFilledChecklist(::Config.accessList.icap, al.request, dash_str);
        if (!::Config.accessList.icap || checklist->fastCheck()) {
            finalizeLogInfo();
            icapLogLog(&al, checklist);
        }
        accessLogFreeMemory(&al);
        delete checklist;
    }
}