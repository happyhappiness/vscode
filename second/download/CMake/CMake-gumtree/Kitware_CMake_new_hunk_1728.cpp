     again a grey area as the MDTM is not kosher RFC959 */

  FTPSENDF(conn, "MDTM %s", file);



  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);

  if(result)

    return result;



  switch(ftpcode) {

  case 213:

    {

      /* we got a time. Format should be: "YYYYMMDDHHMMSS[.sss]" where the

         last .sss part is optional and means fractions of a second */

      int year, month, day, hour, minute, second;

      if(6 == sscanf(buf+4, "%04d%02d%02d%02d%02d%02d",

                     &year, &month, &day, &hour, &minute, &second)) {

        /* we have a time, reformat it */

        time_t secs=time(NULL);

        sprintf(buf, "%04d%02d%02d %02d:%02d:%02d",

                year, month, day, hour, minute, second);

        /* now, convert this into a time() value: */

        conn->data->info.filetime = curl_getdate(buf, &secs);

      }

    }

    break;

  default:

    infof(conn->data, "unsupported MDTM reply format\n");

    break;

  case 550: /* "No such file or directory" */

    failf(conn->data, "Given file does not exist");

    result = CURLE_FTP_COULDNT_RETR_FILE;

    break;

  }

  return  result;

}

