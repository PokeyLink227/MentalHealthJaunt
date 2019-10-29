#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "stdlib.h"
#include "time.h"


inline int nextInt(std::ifstream *, char);

struct answer {
	std::string text;
	char scores[5];

	answer() {
		text = "N/A";
	}

	answer(std::string &text_in, std::ifstream *in) {
		text = text_in;
		scores[0] = nextInt(in, ' ');
		scores[1] = nextInt(in, ' ');
		scores[2] = nextInt(in, ' ');
		scores[3] = nextInt(in, ' ');
		scores[4] = nextInt(in, '\n');
	}

};

struct question {
	std::string text;
	std::vector<answer> answers;
	char topic;
	bool asked;

	question() {
		text = "N/A";
		asked = false;
	}

	question(std::string &text_in, std::ifstream *in) {
		text = text_in;
		answers = std::vector<answer>(nextInt(in, '\n'));
		asked = false;
		topic = nextInt(in, '\n');
	}
};


inline char sum(char *ray) {
	char total = 0;
	for (char c = 0; c < 5; c++) total += ray[c];
	return total;
}

void read_web(std::vector<question> &);
char *ask_question(question *);


int main() {
	srand(time(0));
	std::vector<question> questions;
	std::vector<std::string> messages = {
		"Depression",
		"ADHD",
		"Anexity",
		"OCD",
		"PTSD"
	};

	char THRESHOLD = 2, MAX_CYCLES = 1;
	char CYCLE = 0;


	read_web(questions);
	int asked = 0;
	char scores[6] = { 0,0,0,0,0 };

	while (CYCLE < MAX_CYCLES && asked < questions.size()) {
		char found = -1;
		if (sum(scores) != 0) {
			int r = rand() % sum(scores);
			for (char c = 0; c < 5; c++) {
				r -= scores[c];
				if (r <= 0 && found == -1) found = c;
			}
		}
		char q = 0, stop = questions.size();
		do { q = rand() % questions.size(); stop--; if (stop == 0) found = -1; } while (questions[q].asked && (found != -1 && questions[q].topic == found));
		char *ret = ask_question(&questions[q]);
		for (char c = 0; c < 5; c++) scores[c] += ret[c];
		bool save = false;
		for (char c = 0; c < 5; c++) if (scores[c] >= THRESHOLD) save = true;
		if (save) CYCLE++;
		asked++;
	}

	std::cout << "ask your doctor about: ";
	bool save = true;
	for (char c = 0; c < 5; c++) if (scores[c] >= THRESHOLD) {
		std::cout << messages[c] << ", ";
		save = false;
	}

	if (save) std::cout << "nothing, your are healthy.";

}

char *ask_question(question *Q) {
	std::cout << (*Q).text << '\n';
	for (int i = 0; i < (*Q).answers.size(); i++) if((*Q).answers[i].text != "%") std::cout << i+1 << ". " << (*Q).answers[i].text << '\n';
	int input = -1;

	while (input <= 0 && input >= (*Q).answers.size()) {
		std::cout << ": ";
		std::cin >> input;
		input--;
	}
	(*Q).asked = true;
	system("cls");
	return (*Q).answers[input].scores;
}

inline int nextInt(std::ifstream *stream, char del) {
	std::string line;
	getline(*stream, line, del);
	std::stringstream x(line);
	int ret;
	x >> ret;
	return ret;
}

void read_web(std::vector<question> &out) {
	std::ifstream file("C:\\Users\\Thomas\\Desktop\\MHJQ.txt");

	int num_questions = nextInt(&file, '\n');  // questions
	out = std::vector<question>(num_questions);
	std::string line;


	for (int i = 0; i < num_questions; i++) {
		getline(file, line); // question name
		out[i] = question(line, &file); // number of answers, topic id
		for (int j = 0; j < out[i].answers.size(); j++) {
			getline(file, line); // answer
			out[i].answers[j] = answer(line, &file); // 5 numbers
		}
	}

}

