Http::StatusCode
Ftp::Client::failedHttpStatus(err_type &error)
{
    if (error == ERR_NONE)
        error = ERR_FTP_FAILURE;
    return error == ERR_READ_TIMEOUT ? Http::scGatewayTimeout :
           Http::scBadGateway;
}