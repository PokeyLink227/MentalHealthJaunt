#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

struct question {
    std::string body;
    answer* answers;
    unsigned int num_answers;
    
    question(std::string &name, int num_answers_in) {
        body = name;
        answers = new answer[num_answers_in];
        num_answers = num_answers_in;
    }
};

struct answer {
    std::string body, code;
    int next;
    
    answer(std::string &name, std::string &code_in, int next_in) {
        body = name;
        code = code_in;
        next = next_in;
    }
};

question *questions;

int main() {
    //read in questions
    std::ifstream in("file");
    int outer_loop, inner_loop, num;
    std::string line, line2, line3;
    
    getline(in, line);
    std::sstream x(line);
    x >> outer_loop;
    
    questions = new question[outer_loop];
    
    for(int i = 0; i < outer_loop; i++) {
        getline(in, line);
        getline(in, line2);
        x = std::sstream(line2);
        x >> num;
        questions[i] = question(line, num);
        
        getline(in, line);
        x = std::sstream(line);
        x >> inner_loop;
        for(int j = 0; j < inner_loop; j++) {
            getline(in, line);
            getline(in, line2);
            getline(in, line3);
            x = std::sstream(line3);
            x >> num;
            questions[i].answers[j] = answer(line, line2, num);
        }
    }
}
