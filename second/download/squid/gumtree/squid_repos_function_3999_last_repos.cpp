int
Acl::ConnectionsEncrypted::match(ACLChecklist *checklist)
{
    if (!checklist->hasRequest()) {
        debugs(28, DBG_IMPORTANT, "WARNING: " << name << " ACL is used in " <<
               "context without an HTTP request. Assuming mismatch.");
        return 0;
    }

    ACLFilledChecklist *filled = Filled((ACLChecklist*)checklist);

    const bool safeRequest =
        !(filled->request->sources & HttpMsg::srcUnsafe);
    const bool safeReply = !filled->reply ||
                           !(filled->reply->sources & HttpMsg::srcUnsafe);

    return (safeRequest && safeReply) ? 1 : 0;
}