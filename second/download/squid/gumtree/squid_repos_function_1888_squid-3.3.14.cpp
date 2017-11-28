static void
errorMsg(const char *filename, int line, const char *detail)
{
    std::cerr << "Error in '" << filename << "' on line " << line <<
              "--> " << detail << std::endl;
}