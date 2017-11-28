Snmp::Var&
Snmp::Var::operator += (const Var& var)
{
    switch (type) {
    case SMI_INTEGER:
        setInt(asInt() + var.asInt());
        break;
    case SMI_GAUGE32:
        setGauge(asGauge() + var.asGauge());
        break;
    case SMI_COUNTER32:
        setCounter(asCounter() + var.asCounter());
        break;
    case SMI_COUNTER64:
        setCounter64(asCounter64() + var.asCounter64());
        break;
    case SMI_TIMETICKS:
        setTimeTicks(asTimeTicks() + var.asTimeTicks());
        break;
    default:
        debugs(49, DBG_CRITICAL, HERE << "Unsupported type: " << type);
        throw TexcHere("Unsupported type");
        break;
    }
    return *this;
}