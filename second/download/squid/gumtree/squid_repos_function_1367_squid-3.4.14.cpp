int
HttpParserParseReqLine(HttpParser *hmsg)
{
    PROF_start(HttpParserParseReqLine);
    int retcode = hmsg->parseRequestFirstLine();
    debugs(74, 5, "Parser: retval " << retcode << ": from " << hmsg->req.start <<
           "->" << hmsg->req.end << ": method " << hmsg->req.m_start << "->" <<
           hmsg->req.m_end << "; url " << hmsg->req.u_start << "->" << hmsg->req.u_end <<
           "; version " << hmsg->req.v_start << "->" << hmsg->req.v_end << " (" << hmsg->req.v_maj <<
           "/" << hmsg->req.v_min << ")");
    PROF_stop(HttpParserParseReqLine);
    return retcode;
}