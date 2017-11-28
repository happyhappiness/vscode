        else if (ap->stillProducing(const_cast<XactionRep*>(this)))
            buf.append(" Ap", 3);
        else
            buf.append(" A?", 3);
    }

    buf.Printf(" %s%u]", id.prefix(), id.value);

    buf.terminate();

    return buf.content();
}

