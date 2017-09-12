static void printCentered(int indent, int width, char* body) {
    char head[256], tail[256];
    memset(head, '\0', 256);
    memset(tail, '\0', 256);

    memset(head, '=', indent);
    memset(tail, '=', width - 2 - indent - strlen(body));
    serverLog(LL_WARNING, "%s %s %s", head, body, tail);
}