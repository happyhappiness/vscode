void
ntlm_dump_ntlmssp_flags(u_int32_t flags)
{
    fprintf(stderr, "flags: %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
            (flags & NEGOTIATE_UNICODE ? "Unicode " : ""),
            (flags & NEGOTIATE_ASCII ? "ASCII " : ""),
            (flags & NEGOTIATE_REQUEST_TARGET ? "ReqTgt " : ""),
            (flags & NEGOTIATE_REQUEST_SIGN ? "ReqSign " : ""),
            (flags & NEGOTIATE_REQUEST_SEAL ? "ReqSeal " : ""),
            (flags & NEGOTIATE_DATAGRAM_STYLE ? "Dgram " : ""),
            (flags & NEGOTIATE_USE_LM ? "UseLM " : ""),
            (flags & NEGOTIATE_USE_NETWARE ? "UseNW " : ""),
            (flags & NEGOTIATE_USE_NTLM ? "UseNTLM " : ""),
            (flags & NEGOTIATE_DOMAIN_SUPPLIED ? "HaveDomain " : ""),
            (flags & NEGOTIATE_WORKSTATION_SUPPLIED ? "HaveWKS " : ""),
            (flags & NEGOTIATE_THIS_IS_LOCAL_CALL ? "LocalCall " : ""),
            (flags & NEGOTIATE_ALWAYS_SIGN ? "AlwaysSign " : ""),
            (flags & CHALLENGE_TARGET_IS_DOMAIN ? "Tgt_is_domain" : ""),
            (flags & CHALLENGE_TARGET_IS_SERVER ? "Tgt_is_server " : ""),
            (flags & CHALLENGE_TARGET_IS_SHARE ? "Tgt_is_share " : ""),
            (flags & REQUEST_INIT_RESPONSE ? "Req_init_response " : ""),
            (flags & REQUEST_ACCEPT_RESPONSE ? "Req_accept_response " : ""),
            (flags & REQUEST_NON_NT_SESSION_KEY ? "Req_nonnt_sesskey " : "")
           );
}