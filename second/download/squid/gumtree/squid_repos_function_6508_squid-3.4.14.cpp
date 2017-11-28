void
Mgr::IntParam::pack(Ipc::TypedMsgHdr& msg) const
{
    msg.putPod(type);
    msg.putInt(array.size());
    typedef std::vector<int>::const_iterator Iterator;
    for (Iterator iter = array.begin(); iter != array.end(); ++iter)
        msg.putInt(*iter);
}