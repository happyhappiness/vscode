const Ipc::StoreMapAnchor &
Rock::IoState::readAnchor() const
{
    assert(readableAnchor_);
    return *readableAnchor_;
}