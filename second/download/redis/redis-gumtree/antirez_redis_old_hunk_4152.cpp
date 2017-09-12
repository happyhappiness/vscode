    if (feof(fp) && multi && strlen(error) == 0) {
        ERROR("Reached EOF before reading EXEC for MULTI");
    }

    if (strlen(error) > 0) {
        printf("%s\n", error);
    }

    return pos;
}

