Ipc::StoreMapAnchor &
Rock::IoState::writeAnchor()
{
    assert(writeableAnchor_);
    return *writeableAnchor_;
}