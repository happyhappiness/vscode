Ssl::CertificateStorageAction::Pointer
Ssl::CertificateStorageAction::Create(const Mgr::Command::Pointer &aCmd)
{
    return new CertificateStorageAction(aCmd);
}