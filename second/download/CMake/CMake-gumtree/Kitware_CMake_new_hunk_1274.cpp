  return retVal;

}





int main(int argc, char **argv)

{

  int retVal = 0;



  curl_global_init(CURL_GLOBAL_DEFAULT);



  if(argc>1)

    {

    retVal += GetWebFiles(argv[1], 0);

    }

  else

    {

    printf("error: first argument should be a url to download\n");

    retVal = 1;

    }



  /* Do not check the output of FTP socks5 cannot handle FTP yet */

  /* GetFtpFile(); */

  /* do not test ftp right now because we don't enable that port */



  curl_global_cleanup();



  return retVal;

}
