SBuf
AccessLogEntry::getLogMethod() const
{
    SBuf method;
    if (icp.opcode)
        method.append(icp_opcode_str[icp.opcode]);
    else if (htcp.opcode)
        method.append(htcp.opcode);
    else
        method = http.method.image();
    return method;
}