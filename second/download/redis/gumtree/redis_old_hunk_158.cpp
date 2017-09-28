        memcpy(target, (void*)((size_t)p.data + p.offset), num);
        if (!peek) positions[level].offset += num;
    }
    return 1;
}

int processHeader() {
    char buf[10] = "_________";
    int dump_version;

    if (!readBytes(buf, 9)) {
        ERROR("Cannot read header\n");
    }
