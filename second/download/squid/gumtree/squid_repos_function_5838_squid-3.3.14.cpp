Snmp::Var&
Snmp::Var::operator /= (int num)
{
    Must(num != 0);
    switch (type) {
    case SMI_INTEGER:
        setInt(asInt() / num);
        break;
    case SMI_GAUGE32:
        setGauge(asGauge() / num);
        break;
    case SMI_COUNTER32:
        setCounter(asCounter() / num);
        break;
    case SMI_COUNTER64:
        setCounter64(asCounter64() / num);
        break;
    case SMI_TIMETICKS:
        setTimeTicks(asTimeTicks() / num);
        break;
    default:
        debugs(49, DBG_CRITICAL, HERE << "Unsupported type: " << type);
        throw TexcHere("Unsupported type");
        break;
    }
    return *this;
}