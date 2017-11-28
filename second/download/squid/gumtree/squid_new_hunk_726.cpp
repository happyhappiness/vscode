
    buf.append(" [", 2);
    if (stopReason != NULL) {
        buf.Printf("Stopped, reason:");
        buf.Printf("%s",stopReason);
    }
    buf.Printf(" %s%u]", id.prefix(), id.value);
    buf.terminate();

    return buf.content();
}

