const Ftp::MasterState &
Ftp::Relay::master() const
{
    return const_cast<Ftp::Relay*>(this)->updateMaster(); // avoid code dupe
}