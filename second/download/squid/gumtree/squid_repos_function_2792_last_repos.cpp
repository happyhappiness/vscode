SBuf &
URL::absolute() const
{
    if (absolute_.isEmpty()) {
        // TODO: most URL will be much shorter, avoid allocating this much
        absolute_.reserveCapacity(MAX_URL);

        absolute_.append(getScheme().image());
        absolute_.append(":",1);
        if (getScheme() != AnyP::PROTO_URN) {
            absolute_.append("//", 2);
            const bool omitUserInfo = getScheme() == AnyP::PROTO_HTTP ||
                                      getScheme() != AnyP::PROTO_HTTPS ||
                                      userInfo().isEmpty();
            if (!omitUserInfo) {
                absolute_.append(userInfo());
                absolute_.append("@", 1);
            }
            absolute_.append(authority());
        }
        absolute_.append(path());
    }

    return absolute_;
}