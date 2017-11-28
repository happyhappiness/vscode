bool gotHello() { return (helloState == atHelloReceived); }
    /// Return the SSL features requested by SSL client
    const Bio::sslFeatures &getFeatures() const {return features;}
    /// Prevents or allow writting on socket.
    void hold(bool h) {holdRead_ = holdWrite_ = h;}

private:
    /// True if the SSL state corresponds to a hello message
    bool isClientHello(int state);