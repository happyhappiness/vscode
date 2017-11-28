unsigned int
Snmp::Var::asGauge() const
{
    Must(type == SMI_GAUGE32);
    Must(val.integer != NULL && val_len == 4);
    return *reinterpret_cast<unsigned int*>(val.integer);
}