void
Adaptation::Ecap::XactionRep::visitEachOption(libecap::NamedValueVisitor &visitor) const
{
    if (const libecap::Area value = clientIpValue())
        visitor.visit(libecap::metaClientIp, value);
    if (const libecap::Area value = usernameValue())
        visitor.visit(libecap::metaUserName, value);

    if (Adaptation::Config::masterx_shared_name) {
        const libecap::Name name(Adaptation::Config::masterx_shared_name);
        if (const libecap::Area value = masterxSharedValue(name))
            visitor.visit(name, value);
    }

    visitEachMetaHeader(visitor);

    // TODO: metaServerIp, metaAuthenticatedUser, and metaAuthenticatedGroups
}