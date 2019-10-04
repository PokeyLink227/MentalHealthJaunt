struct question {
    std::string body;
    answer* answers;
    unsigned int num_answers;
    
    question() {}
};

struct answer {
    std::string body;
    question* next;
    
    answer() {}
};
