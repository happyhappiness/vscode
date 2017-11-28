long long int
Snmp::Var::asCounter64() const
{
    Must(type == SMI_COUNTER64);
    Must(val.integer != NULL && val_len == 8);
    return *reinterpret_cast<long long int*>(val.integer);
}