static int isSecureUpgradeable (const request_rec *r)
{
        return isSecureConnUpgradeable (r->server, r->connection);
}