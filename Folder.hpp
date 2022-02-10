#include <vector>
#include "Note.hpp"

using namespace std;

class Folder {
private:
	string name;
	vector<Folder*> folders;
	vector<Note*> notes;

public:
	Folder(string name) {
		this->name = name;
	}
	~Folder() {
		for (int i = folders.size() - 1; i >= 0; i--) {
			delete folders[i];
			folders.erase(folders.begin() + i);
		}
		for (int i = notes.size() - 1; i >= 0; i--) {
			delete notes[i];
			notes.erase(notes.begin() + i);
		}
		
	}
	void createFolder(string name) {
		Folder* folder = new Folder(name);
		folders.push_back(folder);	
	}
	void createNote(string name) {
		Note* note = new Note(name);
		notes.push_back(note);
	}
	void sortFolders(int iMin, int iMax) {
		int gauche = iMin, pivot = iMin;
		int droite = iMax;
		while (gauche != droite) {
			if (folders[gauche]->getName() > folders[droite]->getName()) {
				swap(folders[gauche], folders[droite]);
				pivot = gauche + droite - pivot;
			}
			(pivot == gauche) ? droite--: gauche++; 	
		}
		if (iMin < pivot - 1) {
			sortFolders(iMin, pivot - 1);
		}	
		if (pivot + 1 < iMax){
			sortFolders(pivot + 1, iMax);
		}
	}
	void sortNotes(int iMin, int iMax) {
		int gauche = iMin, pivot = iMin;
		int droite = iMax;
		while (gauche != droite) {
			if (notes[gauche]->getName() > notes[droite]->getName()) {
				swap(notes[gauche], notes[droite]);
				pivot = gauche + droite - pivot;
			}
			(pivot == gauche) ? droite--: gauche++; 	
		}
		if (iMin < pivot - 1) {
			sortNotes(iMin, pivot - 1);
		}	
		if (pivot + 1 < iMax){
			sortNotes(pivot + 1, iMax);
		}
	}
	string getName() {
		return name;
	}
	Folder* getFolder(size_t index) {
		return folders[index];
	}
	Note* getNote(size_t index) {
		return notes[index];
	}
	size_t getNbFolder() {
		return folders.size();
	}
	size_t getNbNote() {
		return notes.size();
	}
	void setName(string name) {
		this->name = name;
	}
	void deleteFolder(int index) {
		delete folders[index];
		folders.erase(folders.begin() + index);
	}
	void deleteNote(int index) {
		delete notes[index];
		notes.erase(notes.begin() + index);
	}
};
