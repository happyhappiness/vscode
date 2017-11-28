void Ipc::Coordinator::receive(const TypedMsgHdr& message)
{
    switch (message.type()) {
    case mtRegistration:
        debugs(54, 6, HERE << "Registration request");
        handleRegistrationRequest(HereIamMessage(message));
        break;

    case mtStrandSearchRequest: {
        const StrandSearchRequest sr(message);
        debugs(54, 6, HERE << "Strand search request: " << sr.requestorId <<
               " tag: " << sr.tag);
        handleSearchRequest(sr);
        break;
    }

    case mtSharedListenRequest:
        debugs(54, 6, HERE << "Shared listen request");
        handleSharedListenRequest(SharedListenRequest(message));
        break;

    case mtCacheMgrRequest: {
        debugs(54, 6, HERE << "Cache manager request");
        const Mgr::Request req(message);
        handleCacheMgrRequest(req);
    }
    break;

    case mtCacheMgrResponse: {
        debugs(54, 6, HERE << "Cache manager response");
        const Mgr::Response resp(message);
        handleCacheMgrResponse(resp);
    }
    break;

#if SQUID_SNMP
    case mtSnmpRequest: {
        debugs(54, 6, HERE << "SNMP request");
        const Snmp::Request req(message);
        handleSnmpRequest(req);
    }
    break;

    case mtSnmpResponse: {
        debugs(54, 6, HERE << "SNMP response");
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