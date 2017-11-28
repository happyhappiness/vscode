Ssl::CertificateStorageAction::Pointer
Ssl::CertificateStorageAction::Create(const Mgr::Command::Pointer &cmd)
{
    return new CertificateStorageAction(cmd);
}