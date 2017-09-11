    }
}

int main(int argc, char **argv) {
    uint8_t success;
    int i;
    intset *is;
    sranddev();

    printf("Value encodings: "); {
        assert(_intsetValueEncoding(-32768) == INTSET_ENC_INT16);
