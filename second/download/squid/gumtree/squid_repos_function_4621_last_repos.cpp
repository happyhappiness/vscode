Http::Stream *
Ftp::Server::earlyError(const EarlyErrorKind eek)
{
    /* Default values, to be updated by the switch statement below */
    int scode = 421;
    const char *reason = "Internal error";
    const char *errUri = "error:ftp-internal-early-error";

    switch (eek) {
    case EarlyErrorKind::HugeRequest:
        scode = 421;
        reason = "Huge request";
        errUri = "error:ftp-huge-request";
        break;

    case EarlyErrorKind::MissingLogin:
        scode = 530;
        reason = "Must login first";
        errUri = "error:ftp-must-login-first";
        break;

    case EarlyErrorKind::MissingUsername:
        scode = 501;
        reason = "Missing username";
        errUri = "error:ftp-missing-username";
        break;

    case EarlyErrorKind::MissingHost:
        scode = 501;
        reason = "Missing host";
        errUri = "error:ftp-missing-host";
        break;

    case EarlyErrorKind::UnsupportedCommand:
        scode = 502;
        reason = "Unknown or unsupported command";
        errUri = "error:ftp-unsupported-command";
        break;

    case EarlyErrorKind::InvalidUri:
        scode = 501;
        reason = "Invalid URI";
        errUri = "error:ftp-invalid-uri";
        break;

    case EarlyErrorKind::MalformedCommand:
        scode = 421;
        reason = "Malformed command";
        errUri = "error:ftp-malformed-command";
        break;

        // no default so that a compiler can check that we have covered all cases
    }

    Http::Stream *context = abortRequestParsing(errUri);
    clientStreamNode *node = context->getClientReplyContext();
    Must(node);
    clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
    Must(repContext);

    // We cannot relay FTP scode/reason via HTTP-specific ErrorState.
    // TODO: When/if ErrorState can handle native FTP errors, use it instead.
    HttpReply *reply = Ftp::HttpReplyWrapper(scode, reason, Http::scBadRequest, -1);
    repContext->setReplyToReply(reply);
    return context;
}