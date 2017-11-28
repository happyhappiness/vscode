void
Mgr::QueryParams::unpack(const Ipc::TypedMsgHdr& msg)
{
    int count = msg.getInt();
    Must(count >= 0);
    params.clear();
    for ( ; count > 0; --count) {
        String name;
        msg.getString(name);
        Must(name.size() != 0);
        QueryParam::Type type;
        msg.getPod(type);
        QueryParam::Pointer value = CreateParam(type);
        value->unpackValue(msg);
        params.push_back(Param(name, value));
    }
}