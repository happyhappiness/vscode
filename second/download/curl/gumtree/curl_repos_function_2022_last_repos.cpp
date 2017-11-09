static CURLcode getinfo_offt(struct Curl_easy *data, CURLINFO info,
                             curl_off_t *param_offt)
{
  switch(info) {
  case CURLINFO_SIZE_UPLOAD_T:
    *param_offt = data->progress.uploaded;
    break;
  case CURLINFO_SIZE_DOWNLOAD_T:
    *param_offt = data->progress.downloaded;
    break;
  case CURLINFO_SPEED_DOWNLOAD_T:
    *param_offt =  data->progress.dlspeed;
    break;
  case CURLINFO_SPEED_UPLOAD_T:
    *param_offt = data->progress.ulspeed;
    break;
  case CURLINFO_CONTENT_LENGTH_DOWNLOAD_T:
    *param_offt = (data->progress.flags & PGRS_DL_SIZE_KNOWN)?
      data->progress.size_dl:-1;
    break;
  case CURLINFO_CONTENT_LENGTH_UPLOAD_T:
    *param_offt = (data->progress.flags & PGRS_UL_SIZE_KNOWN)?
      data->progress.size_ul:-1;
    break;
  default:
    return CURLE_UNKNOWN_OPTION;
  }

  return CURLE_OK;
}