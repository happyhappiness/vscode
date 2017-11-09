int main(int argc, char *argv[])
{
  CURL *conn = NULL;
  CURLcode code;
  std::string title;

  // Ensure one argument is given

  if(argc != 2) {
    fprintf(stderr, "Usage: %s <url>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  curl_global_init(CURL_GLOBAL_DEFAULT);

  // Initialize CURL connection

  if(!init(conn, argv[1])) {
    fprintf(stderr, "Connection initializion failed\n");
    exit(EXIT_FAILURE);
  }

  // Retrieve content for the URL

  code = curl_easy_perform(conn);
  curl_easy_cleanup(conn);

  if(code != CURLE_OK) {
    fprintf(stderr, "Failed to get '%s' [%s]\n", argv[1], errorBuffer);
    exit(EXIT_FAILURE);
  }

  // Parse the (assumed) HTML code
  parseHtml(buffer, title);

  // Display the extracted title
  printf("Title: %s\n", title.c_str());

  return EXIT_SUCCESS;
}