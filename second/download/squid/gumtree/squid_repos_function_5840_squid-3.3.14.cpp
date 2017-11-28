bool
Snmp::Var::operator > (const Var& var) const
{
    switch (type) {
    case SMI_INTEGER:
        return asInt() > var.asInt();
    case SMI_GAUGE32:
        return asGauge() > var.asGauge();
    case SMI_COUNTER32:
        return asCounter() > var.asCounter();
    case SMI_COUNTER64:
        return asCounter64() > var.asCounter64();
    case SMI_TIMETICKS:
        return asTimeTicks() > var.asTimeTicks();
    default:
        debugs(49, DBG_CRITICAL, HERE << "Unsupported type: " << type);
        throw TexcHere("Unsupported type");
        break;
    }
    return false; // unreachable
}