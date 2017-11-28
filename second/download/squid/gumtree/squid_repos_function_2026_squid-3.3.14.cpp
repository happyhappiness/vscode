void addHistory(char const *label, char const *aFile, int aLine) {
        if (calls.size() > 1000)
            return;

        calls.push_back(new CBDataCall(label, aFile, aLine));
    }