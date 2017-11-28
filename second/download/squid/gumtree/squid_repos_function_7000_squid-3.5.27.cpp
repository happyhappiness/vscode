const char *
Ipc::FdNote(int fdNoteId)
{
    static const char *FdNotes[Ipc::fdnEnd] = {
        "None", // fdnNone
        "HTTP Socket", // fdnHttpSocket
        "HTTPS Socket", // fdnHttpsSocket
        "FTP Socket", // fdnFtpSocket
#if SQUID_SNMP
        "Incoming SNMP Socket", // fdnInSnmpSocket
        "Outgoing SNMP Socket", // fdnOutSnmpSocket
#endif
        "Incoming ICP Socket", // fdnInIcpSocket
        "Incoming HTCP Socket" // fdnInHtcpSocket
    };

    if (fdnNone < fdNoteId && fdNoteId < fdnEnd)
        return FdNotes[fdNoteId];

    debugs(54, DBG_IMPORTANT, HERE << "salvaged bug: wrong fd_note ID: " << fdNoteId);
    return FdNotes[fdnNone];
}