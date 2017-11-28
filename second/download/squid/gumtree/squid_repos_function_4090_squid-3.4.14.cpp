void Adaptation::Icap::ModXact::makeAllowHeader(MemBuf &buf)
{
    const bool allow204in = preview.enabled(); // TODO: add shouldAllow204in()
    const bool allow204out = state.allowedPostview204 = shouldAllow204();
    const bool allow206in = state.allowedPreview206 = shouldAllow206in();
    const bool allow206out = state.allowedPostview206 = shouldAllow206out();

    debugs(93,9, HERE << "Allows: " << allow204in << allow204out <<
           allow206in << allow206out);

    const bool allow204 = allow204in || allow204out;
    const bool allow206 = allow206in || allow206out;

    if (!allow204 && !allow206)
        return; // nothing to do

    if (virginBody.expected()) // if there is a virgin body, plan to send it
        virginBodySending.plan();

    // writing Preview:...   means we will honor 204 inside preview
    // writing Allow/204     means we will honor 204 outside preview
    // writing Allow:206     means we will honor 206 inside preview
    // writing Allow:204,206 means we will honor 206 outside preview
    const char *allowHeader = NULL;
    if (allow204out && allow206)
        allowHeader = "Allow: 204, 206\r\n";
    else if (allow204out)
        allowHeader = "Allow: 204\r\n";
    else if (allow206)
        allowHeader = "Allow: 206\r\n";

    if (allowHeader) { // may be nil if only allow204in is true
        buf.append(allowHeader, strlen(allowHeader));
        debugs(93,5, HERE << "Will write " << allowHeader);
    }
}