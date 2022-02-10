#include <string>

using namespace std;

class Note {
private:
	string name;
	string content;

public:
	Note(string name) {
		this->name = name;
		this->content = "";

	}
	~Note() {
		
	}
	string getName() {
		return name;
	}
	string getContent() {
		return content;
	}
	void setContent(string content) {
		this->content = content;
	}
	void setName(string name) {
		this->name = name;
	}
	
};
