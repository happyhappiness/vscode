const char *Curl_sspi_strerror (struct connectdata *conn, int err)
{
#ifndef CURL_DISABLE_VERBOSE_STRINGS
  char txtbuf[80];
  char msgbuf[sizeof(conn->syserr_buf)];
  char *p, *str, *msg = NULL;
  bool msg_formatted = FALSE;
  int old_errno;
#endif
  const char *txt;
  char *outbuf;
  size_t outmax;

  DEBUGASSERT(conn);

  outbuf = conn->syserr_buf;
  outmax = sizeof(conn->syserr_buf)-1;
  *outbuf = '\0';

#ifndef CURL_DISABLE_VERBOSE_STRINGS

  old_errno = ERRNO;

  switch(err) {
    case SEC_E_OK:
      txt = "No error";
      break;
    case CRYPT_E_REVOKED:
      txt = "CRYPT_E_REVOKED";
      break;
    case SEC_E_ALGORITHM_MISMATCH:
      txt = "SEC_E_ALGORITHM_MISMATCH";
      break;
    case SEC_E_BAD_BINDINGS:
      txt = "SEC_E_BAD_BINDINGS";
      break;
    case SEC_E_BAD_PKGID:
      txt = "SEC_E_BAD_PKGID";
      break;
    case SEC_E_BUFFER_TOO_SMALL:
      txt = "SEC_E_BUFFER_TOO_SMALL";
      break;
    case SEC_E_CANNOT_INSTALL:
      txt = "SEC_E_CANNOT_INSTALL";
      break;
    case SEC_E_CANNOT_PACK:
      txt = "SEC_E_CANNOT_PACK";
      break;
    case SEC_E_CERT_EXPIRED:
      txt = "SEC_E_CERT_EXPIRED";
      break;
    case SEC_E_CERT_UNKNOWN:
      txt = "SEC_E_CERT_UNKNOWN";
      break;
    case SEC_E_CERT_WRONG_USAGE:
      txt = "SEC_E_CERT_WRONG_USAGE";
      break;
    case SEC_E_CONTEXT_EXPIRED:
      txt = "SEC_E_CONTEXT_EXPIRED";
      break;
    case SEC_E_CROSSREALM_DELEGATION_FAILURE:
      txt = "SEC_E_CROSSREALM_DELEGATION_FAILURE";
      break;
    case SEC_E_CRYPTO_SYSTEM_INVALID:
      txt = "SEC_E_CRYPTO_SYSTEM_INVALID";
      break;
    case SEC_E_DECRYPT_FAILURE:
      txt = "SEC_E_DECRYPT_FAILURE";
      break;
    case SEC_E_DELEGATION_POLICY:
      txt = "SEC_E_DELEGATION_POLICY";
      break;
    case SEC_E_DELEGATION_REQUIRED:
      txt = "SEC_E_DELEGATION_REQUIRED";
      break;
    case SEC_E_DOWNGRADE_DETECTED:
      txt = "SEC_E_DOWNGRADE_DETECTED";
      break;
    case SEC_E_ENCRYPT_FAILURE:
      txt = "SEC_E_ENCRYPT_FAILURE";
      break;
    case SEC_E_ILLEGAL_MESSAGE:
      txt = "SEC_E_ILLEGAL_MESSAGE";
      break;
    case SEC_E_INCOMPLETE_CREDENTIALS:
      txt = "SEC_E_INCOMPLETE_CREDENTIALS";
      break;
    case SEC_E_INCOMPLETE_MESSAGE:
      txt = "SEC_E_INCOMPLETE_MESSAGE";
      break;
    case SEC_E_INSUFFICIENT_MEMORY:
      txt = "SEC_E_INSUFFICIENT_MEMORY";
      break;
    case SEC_E_INTERNAL_ERROR:
      txt = "SEC_E_INTERNAL_ERROR";
      break;
    case SEC_E_INVALID_HANDLE:
      txt = "SEC_E_INVALID_HANDLE";
      break;
    case SEC_E_INVALID_PARAMETER:
      txt = "SEC_E_INVALID_PARAMETER";
      break;
    case SEC_E_INVALID_TOKEN:
      txt = "SEC_E_INVALID_TOKEN";
      break;
    case SEC_E_ISSUING_CA_UNTRUSTED:
      txt = "SEC_E_ISSUING_CA_UNTRUSTED";
      break;
    case SEC_E_ISSUING_CA_UNTRUSTED_KDC:
      txt = "SEC_E_ISSUING_CA_UNTRUSTED_KDC";
      break;
    case SEC_E_KDC_CERT_EXPIRED:
      txt = "SEC_E_KDC_CERT_EXPIRED";
      break;
    case SEC_E_KDC_CERT_REVOKED:
      txt = "SEC_E_KDC_CERT_REVOKED";
      break;
    case SEC_E_KDC_INVALID_REQUEST:
      txt = "SEC_E_KDC_INVALID_REQUEST";
      break;
    case SEC_E_KDC_UNABLE_TO_REFER:
      txt = "SEC_E_KDC_UNABLE_TO_REFER";
      break;
    case SEC_E_KDC_UNKNOWN_ETYPE:
      txt = "SEC_E_KDC_UNKNOWN_ETYPE";
      break;
    case SEC_E_LOGON_DENIED:
      txt = "SEC_E_LOGON_DENIED";
      break;
    case SEC_E_MAX_REFERRALS_EXCEEDED:
      txt = "SEC_E_MAX_REFERRALS_EXCEEDED";
      break;
    case SEC_E_MESSAGE_ALTERED:
      txt = "SEC_E_MESSAGE_ALTERED";
      break;
    case SEC_E_MULTIPLE_ACCOUNTS:
      txt = "SEC_E_MULTIPLE_ACCOUNTS";
      break;
    case SEC_E_MUST_BE_KDC:
      txt = "SEC_E_MUST_BE_KDC";
      break;
    case SEC_E_NOT_OWNER:
      txt = "SEC_E_NOT_OWNER";
      break;
    case SEC_E_NO_AUTHENTICATING_AUTHORITY:
      txt = "SEC_E_NO_AUTHENTICATING_AUTHORITY";
      break;
    case SEC_E_NO_CREDENTIALS:
      txt = "SEC_E_NO_CREDENTIALS";
      break;
    case SEC_E_NO_IMPERSONATION:
      txt = "SEC_E_NO_IMPERSONATION";
      break;
    case SEC_E_NO_IP_ADDRESSES:
      txt = "SEC_E_NO_IP_ADDRESSES";
      break;
    case SEC_E_NO_KERB_KEY:
      txt = "SEC_E_NO_KERB_KEY";
      break;
    case SEC_E_NO_PA_DATA:
      txt = "SEC_E_NO_PA_DATA";
      break;
    case SEC_E_NO_S4U_PROT_SUPPORT:
      txt = "SEC_E_NO_S4U_PROT_SUPPORT";
      break;
    case SEC_E_NO_TGT_REPLY:
      txt = "SEC_E_NO_TGT_REPLY";
      break;
    case SEC_E_OUT_OF_SEQUENCE:
      txt = "SEC_E_OUT_OF_SEQUENCE";
      break;
    case SEC_E_PKINIT_CLIENT_FAILURE:
      txt = "SEC_E_PKINIT_CLIENT_FAILURE";
      break;
    case SEC_E_PKINIT_NAME_MISMATCH:
      txt = "SEC_E_PKINIT_NAME_MISMATCH";
      break;
    case SEC_E_POLICY_NLTM_ONLY:
      txt = "SEC_E_POLICY_NLTM_ONLY";
      break;
    case SEC_E_QOP_NOT_SUPPORTED:
      txt = "SEC_E_QOP_NOT_SUPPORTED";
      break;
    case SEC_E_REVOCATION_OFFLINE_C:
      txt = "SEC_E_REVOCATION_OFFLINE_C";
      break;
    case SEC_E_REVOCATION_OFFLINE_KDC:
      txt = "SEC_E_REVOCATION_OFFLINE_KDC";
      break;
    case SEC_E_SECPKG_NOT_FOUND:
      txt = "SEC_E_SECPKG_NOT_FOUND";
      break;
    case SEC_E_SECURITY_QOS_FAILED:
      txt = "SEC_E_SECURITY_QOS_FAILED";
      break;
    case SEC_E_SHUTDOWN_IN_PROGRESS:
      txt = "SEC_E_SHUTDOWN_IN_PROGRESS";
      break;
    case SEC_E_SMARTCARD_CERT_EXPIRED:
      txt = "SEC_E_SMARTCARD_CERT_EXPIRED";
      break;
    case SEC_E_SMARTCARD_CERT_REVOKED:
      txt = "SEC_E_SMARTCARD_CERT_REVOKED";
      break;
    case SEC_E_SMARTCARD_LOGON_REQUIRED:
      txt = "SEC_E_SMARTCARD_LOGON_REQUIRED";
      break;
    case SEC_E_STRONG_CRYPTO_NOT_SUPPORTED:
      txt = "SEC_E_STRONG_CRYPTO_NOT_SUPPORTED";
      break;
    case SEC_E_TARGET_UNKNOWN:
      txt = "SEC_E_TARGET_UNKNOWN";
      break;
    case SEC_E_TIME_SKEW:
      txt = "SEC_E_TIME_SKEW";
      break;
    case SEC_E_TOO_MANY_PRINCIPALS:
      txt = "SEC_E_TOO_MANY_PRINCIPALS";
      break;
    case SEC_E_UNFINISHED_CONTEXT_DELETED:
      txt = "SEC_E_UNFINISHED_CONTEXT_DELETED";
      break;
    case SEC_E_UNKNOWN_CREDENTIALS:
      txt = "SEC_E_UNKNOWN_CREDENTIALS";
      break;
    case SEC_E_UNSUPPORTED_FUNCTION:
      txt = "SEC_E_UNSUPPORTED_FUNCTION";
      break;
    case SEC_E_UNSUPPORTED_PREAUTH:
      txt = "SEC_E_UNSUPPORTED_PREAUTH";
      break;
    case SEC_E_UNTRUSTED_ROOT:
      txt = "SEC_E_UNTRUSTED_ROOT";
      break;
    case SEC_E_WRONG_CREDENTIAL_HANDLE:
      txt = "SEC_E_WRONG_CREDENTIAL_HANDLE";
      break;
    case SEC_E_WRONG_PRINCIPAL:
      txt = "SEC_E_WRONG_PRINCIPAL";
      break;
    case SEC_I_COMPLETE_AND_CONTINUE:
      txt = "SEC_I_COMPLETE_AND_CONTINUE";
      break;
    case SEC_I_COMPLETE_NEEDED:
      txt = "SEC_I_COMPLETE_NEEDED";
      break;
    case SEC_I_CONTEXT_EXPIRED:
      txt = "SEC_I_CONTEXT_EXPIRED";
      break;
    case SEC_I_CONTINUE_NEEDED:
      txt = "SEC_I_CONTINUE_NEEDED";
      break;
    case SEC_I_INCOMPLETE_CREDENTIALS:
      txt = "SEC_I_INCOMPLETE_CREDENTIALS";
      break;
    case SEC_I_LOCAL_LOGON:
      txt = "SEC_I_LOCAL_LOGON";
      break;
    case SEC_I_NO_LSA_CONTEXT:
      txt = "SEC_I_NO_LSA_CONTEXT";
      break;
    case SEC_I_RENEGOTIATE:
      txt = "SEC_I_RENEGOTIATE";
      break;
    case SEC_I_SIGNATURE_NEEDED:
      txt = "SEC_I_SIGNATURE_NEEDED";
      break;
    default:
      txt = "Unknown error";
  }

  if(err == SEC_E_OK)
    strncpy(outbuf, txt, outmax);
  else if(err == SEC_E_ILLEGAL_MESSAGE)
    snprintf(outbuf, outmax,
             "SEC_E_ILLEGAL_MESSAGE (0x%08X) - This error usually occurs "
             "when a fatal SSL/TLS alert is received (e.g. handshake failed). "
             "More detail may be available in the Windows System event log.",
             err);
  else {
    str = txtbuf;
    snprintf(txtbuf, sizeof(txtbuf), "%s (0x%08X)", txt, err);
    txtbuf[sizeof(txtbuf)-1] = '\0';

#ifdef _WIN32_WCE
    {
      wchar_t wbuf[256];
      wbuf[0] = L'\0';

      if(FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
                       FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, err, LANG_NEUTRAL,
                       wbuf, sizeof(wbuf)/sizeof(wchar_t), NULL)) {
        wcstombs(msgbuf, wbuf, sizeof(msgbuf)-1);
        msg_formatted = TRUE;
      }
    }
#else
    if(FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM |
                      FORMAT_MESSAGE_IGNORE_INSERTS,
                      NULL, err, LANG_NEUTRAL,
                      msgbuf, sizeof(msgbuf)-1, NULL)) {
      msg_formatted = TRUE;
    }
#endif
    if(msg_formatted) {
      msgbuf[sizeof(msgbuf)-1] = '\0';
      /* strip trailing '\r\n' or '\n' */
      p = strrchr(msgbuf, '\n');
      if(p && (p - msgbuf) >= 2)
        *p = '\0';
      p = strrchr(msgbuf, '\r');
      if(p && (p - msgbuf) >= 1)
        *p = '\0';
      msg = msgbuf;
    }
    if(msg)
      snprintf(outbuf, outmax, "%s - %s", str, msg);
    else
      strncpy(outbuf, str, outmax);
  }

  if(old_errno != ERRNO)
    SET_ERRNO(old_errno);

#else

  if(err == SEC_E_OK)
    txt = "No error";
  else
    txt = "Error";

  strncpy(outbuf, txt, outmax);

#endif

  outbuf[outmax] = '\0';

  return outbuf;
}