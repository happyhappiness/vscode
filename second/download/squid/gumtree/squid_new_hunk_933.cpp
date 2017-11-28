        else if (ap->stillProducing(const_cast<XactionRep*>(this)))
            buf.append(" Ap", 3);
        else
            buf.append(" A?", 3);
    }

    buf.appendf(" %s%u]", id.prefix(), id.value);

    buf.terminate();

    return buf.content();
}

void
Adaptation::Ecap::XactionRep::updateSources(HttpMsg *adapted)
{
    adapted->sources |= service().cfg().connectionEncryption ? HttpMsg::srcEcaps : HttpMsg::srcEcap;
}

