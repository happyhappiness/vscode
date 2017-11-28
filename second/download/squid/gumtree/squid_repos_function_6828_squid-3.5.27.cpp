void
Ipc::TypedMsgHdr::setType(int aType)
{
    if (data.type_) {
        Must(data.type_ == aType);
    } else {
        allocData();
        data.type_ = aType;
    }
}