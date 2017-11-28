bool Adaptation::Icap::ModXact::validate200Ok()
{
    if (ICAP::methodRespmod == service().cfg().method) {
        if (!gotEncapsulated("res-hdr"))
            return false;

        return true;
    }

    if (ICAP::methodReqmod == service().cfg().method) {
        if (!gotEncapsulated("res-hdr") && !gotEncapsulated("req-hdr"))
            return false;

        return true;
    }

    return false;
}