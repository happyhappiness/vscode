int main(int argc, char **argv)
{
    CURL *curl_handle;
    char headerfilename[FILENAME_MAX] = "head.out";
    FILE *headerfile;
    int rc=0;
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle,   CURLOPT_URL        
,"http://curl.haxx.se");
    curl_easy_setopt(curl_handle,   CURLOPT_NOPROGRESS  ,1);
    curl_easy_setopt(curl_handle,   CURLOPT_MUTE        ,1);
    curl_easy_setopt(curl_handle,   CURLOPT_WRITEFUNCTION,&write_data);
    headerfile = fopen(headerfilename,"w");
    if (headerfile == NULL) {
        curl_easy_cleanup(curl_handle);
        return -1;
    }
    curl_easy_setopt(curl_handle,   CURLOPT_WRITEHEADER ,headerfile);
    curl_easy_perform(curl_handle);
    printf("The head is <%s>\n",headerfilename);
    fclose(headerfile);
    curl_easy_cleanup(curl_handle);
    return 0;
}