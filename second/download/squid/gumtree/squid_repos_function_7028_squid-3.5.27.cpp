void Ipc::Strand::receive(const TypedMsgHdr &message)
{
    debugs(54, 6, HERE << message.type());
    switch (message.type()) {

    case mtRegistration:
        handleRegistrationResponse(HereIamMessage(message));
        break;

    case mtSharedListenResponse:
        SharedListenJoined(SharedListenResponse(message));
        break;

#if USE_DISKIO_IPCIO
    case mtStrandSearchResponse:
        IpcIoFile::HandleOpenResponse(StrandSearchResponse(message));
        break;

    case mtIpcIoNotification:
        IpcIoFile::HandleNotification(message);
        break;
#endif /* USE_DISKIO_IPCIO */

    case mtCacheMgrRequest: {
        const Mgr::Request req(message);
        handleCacheMgrRequest(req);
    }
    break;

    case mtCacheMgrResponse: {
        const Mgr::Response resp(message);
        handleCacheMgrResponse(resp);
    }
    break;

    case mtCollapsedForwardingNotification:
        CollapsedForwarding::HandleNotification(message);
        break;

#if SQUID_SNMP
    case mtSnmpRequest: {
        const Snmp::Request req(message);
        handleSnmpRequest(req);
    }
    break;

    case mtSnmpResponse: {
        const Snmp::Response resp(message);
        handleSnmpResponse(resp);
    }
    break;
#endif

    default:
        debugs(54, DBG_IMPORTANT, HERE << "Unhandled message type: " << message.type());
        break;
    }
}