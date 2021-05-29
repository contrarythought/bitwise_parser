class Token_stream {
    public:
        Token get();
        void putback(Token t);
    private:
        bool is_full = false;
        Token buffer;
};
