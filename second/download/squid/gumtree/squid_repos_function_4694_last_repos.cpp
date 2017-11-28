void
AnyP::UriScheme::Init()
{
    if (LowercaseSchemeNames_.empty()) {
        LowercaseSchemeNames_.reserve(sizeof(SBuf) * AnyP::PROTO_MAX);
        // TODO: use base/EnumIterator.h if possible
        for (int i = AnyP::PROTO_NONE; i < AnyP::PROTO_MAX; ++i) {
            SBuf image(ProtocolType_str[i]);
            image.toLower();
            LowercaseSchemeNames_.emplace_back(image);
        }
    }
}