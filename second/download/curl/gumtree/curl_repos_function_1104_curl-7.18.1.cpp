void Curl_easy_initHandleData(struct SessionHandle *data)
{
    memset(&data->req, 0, sizeof(struct SingleRequest));

    data->req.maxdownload = -1;
}