void
ntlm_dump_ntlmssp_flags(uint32_t flags)
{
    fprintf(stderr, "flags: %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
            (flags & NTLM_NEGOTIATE_UNICODE ? "Unicode " : ""),
            (flags & NTLM_NEGOTIATE_ASCII ? "ASCII " : ""),
            (flags & NTLM_NEGOTIATE_REQUEST_TARGET ? "ReqTgt " : ""),
            (flags & NTLM_NEGOTIATE_REQUEST_SIGN ? "ReqSign " : ""),
            (flags & NTLM_NEGOTIATE_REQUEST_SEAL ? "ReqSeal " : ""),
            (flags & NTLM_NEGOTIATE_DATAGRAM_STYLE ? "Dgram " : ""),
            (flags & NTLM_NEGOTIATE_USE_LM ? "UseLM " : ""),
            (flags & NTLM_NEGOTIATE_USE_NETWARE ? "UseNW " : ""),
            (flags & NTLM_NEGOTIATE_USE_NTLM ? "UseNTLM " : ""),
            (flags & NTLM_NEGOTIATE_DOMAIN_SUPPLIED ? "HaveDomain " : ""),
            (flags & NTLM_NEGOTIATE_WORKSTATION_SUPPLIED ? "HaveWKS " : ""),
            (flags & NTLM_NEGOTIATE_THIS_IS_LOCAL_CALL ? "LocalCall " : ""),
            (flags & NTLM_NEGOTIATE_ALWAYS_SIGN ? "AlwaysSign " : ""),
            (flags & NTLM_CHALLENGE_TARGET_IS_DOMAIN ? "Tgt_is_domain" : ""),
            (flags & NTLM_CHALLENGE_TARGET_IS_SERVER ? "Tgt_is_server " : ""),
            (flags & NTLM_CHALLENGE_TARGET_IS_SHARE ? "Tgt_is_share " : ""),
            (flags & NTLM_REQUEST_INIT_RESPONSE ? "Req_init_response " : ""),
            (flags & NTLM_REQUEST_ACCEPT_RESPONSE ? "Req_accept_response " : ""),
            (flags & NTLM_REQUEST_NON_NT_SESSION_KEY ? "Req_nonnt_sesskey " : "")
           );
}