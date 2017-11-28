void
Adaptation::Ecap::StatusLineRep::statusCode(int code)
{
    // TODO: why is .status a enum? Do we not support unknown statuses?
    theMessage.sline.status = static_cast<http_status>(code);
}