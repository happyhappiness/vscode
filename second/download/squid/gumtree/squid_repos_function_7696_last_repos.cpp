int main (int argc, char **argv)
{
    if (CaseSensitiveCheck()) {
        std::cerr << "Case sensitive check failure." << std::endl;
        return 1;
    }

    if (CaseInsensitiveCheck()) {
        std::cerr << "Case in-sensitive check failure." << std::endl;
        return 1;
    }

    return 0;
}