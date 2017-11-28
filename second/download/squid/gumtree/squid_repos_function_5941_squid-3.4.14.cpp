unsigned int
Snmp::Var::asTimeTicks() const
{
    Must(type == SMI_TIMETICKS);
    Must(val.integer != NULL && val_len == sizeof(unsigned int));
    return *reinterpret_cast<unsigned int*>(val.integer);
}