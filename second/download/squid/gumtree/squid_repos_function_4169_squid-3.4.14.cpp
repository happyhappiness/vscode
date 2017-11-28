void Adaptation::Icap::Xaction::setOutcome(const Adaptation::Icap::XactOutcome &xo)
{
    if (al.icap.outcome != xoUnknown) {
        debugs(93, 3, HERE << "Warning: reseting outcome: from " <<
               al.icap.outcome << " to " << xo);
    } else {
        debugs(93, 4, HERE << xo);
    }
    al.icap.outcome = xo;
}