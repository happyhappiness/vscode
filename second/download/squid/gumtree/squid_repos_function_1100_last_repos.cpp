icp_opcode
_icp_common_t::getOpCode() const
{
    if (opcode > static_cast<char>(icp_opcode::ICP_END))
        return ICP_INVALID;

    return static_cast<icp_opcode>(opcode);
}