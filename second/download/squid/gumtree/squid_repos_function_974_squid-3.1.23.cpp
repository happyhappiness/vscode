int
HttpParserParseReqLine(HttpParser *hmsg)
{
    PROF_start(HttpParserParseReqLine);
    int retcode = hmsg->parseRequestFirstLine();
    debugs(74, 5, "Parser: retval " << retcode << ": from " << hmsg->req_start <<
           "->" << hmsg->req_end << ": method " << hmsg->m_start << "->" <<
           hmsg->m_end << "; url " << hmsg->u_start << "->" << hmsg->u_end <<
           "; version " << hmsg->v_start << "->" << hmsg->v_end << " (" << hmsg->v_maj <<
           "/" << hmsg->v_min << ")");
    PROF_stop(HttpParserParseReqLine);
    return retcode;
}