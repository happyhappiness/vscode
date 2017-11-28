int
Snmp::Var::asCounter() const
{
    Must(type == SMI_COUNTER32);
    Must(val.integer != NULL && val_len == 4);
    return *reinterpret_cast<int*>(val.integer);
}