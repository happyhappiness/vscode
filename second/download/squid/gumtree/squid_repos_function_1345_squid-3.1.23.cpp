icp_opcode
_icp_common_t::getOpCode() const
{
    if (opcode > (char)ICP_END)
        return ICP_INVALID;

    return (icp_opcode)opcode;
}