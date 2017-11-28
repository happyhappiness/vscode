void
Ftp::Server::setDataCommand()
{
    ClientHttpRequest *const http = pipeline.front()->http;
    assert(http != NULL);
    HttpRequest *const request = http->request;
    assert(request != NULL);
    HttpHeader &header = request->header;
    header.delById(Http::HdrType::FTP_COMMAND);
    header.putStr(Http::HdrType::FTP_COMMAND, "PASV");
    header.delById(Http::HdrType::FTP_ARGUMENTS);
    header.putStr(Http::HdrType::FTP_ARGUMENTS, "");
    debugs(9, 5, "client data command converted to fake PASV");
}