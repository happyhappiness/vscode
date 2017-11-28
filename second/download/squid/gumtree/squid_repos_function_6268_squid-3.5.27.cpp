std::ostream &
operator <<(std::ostream &os, const SipcIo &sio)
{
    return os << "ipcIo" << sio.worker << '.' << sio.msg.requestId <<
           (sio.msg.command == IpcIo::cmdRead ? 'r' : 'w') << sio.disker;
}