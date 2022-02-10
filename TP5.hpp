#include "Stack.hpp"
#include "Queue.hpp"
#include "BSTree.hpp"
// #include "AVLTree"
#include "Window.hpp"
#include "Folder.hpp"

using namespace std;

Folder* root;
Stack<Folder*>* path;
BSTree<int>* selections;
string title = "";
int getIndex(const int& x, const int& y) {
	
	int xIndex = x / Window::getIconWidth();
	int yIndex = y / Window::getIconHeight(); 
	if (path->size() == 1) {
		return ((Window::getWidth() / Window::getIconWidth()) * yIndex) + xIndex;
	}
	else {
		return ((Window::getWidth() / Window::getIconWidth()) * yIndex) + xIndex - 1;
	}
	
}


void onInit() {
	path = new Stack<Folder*>();
	selections = new BSTree<int>();
	path->push(new Folder("/"));
	path->top()->createFolder("hey");
	path->top()->createNote("yo");
	path->top()->createFolder("Dossier1");
	path->top()->createFolder("Drynish");
	path->top()->createNote("Note1");
	path->top()->createNote("Note0");
	path->top()->createFolder("test");
	Window::setTitle("/");
	title += path->top()->getName();
	path->top()->sortFolders(0, path->top()->getNbFolder() - 1);
	path->top()->sortNotes(0, path->top()->getNbNote() - 1);
}

void onRefresh() {
	int x = 0;
	int y = 0;
	if (path->size() != 1) {
		Window::drawIcon(Icon::FOLDER, x, y);
		Window::drawString("..", x + (Window::getIconWidth() / 2) - (Window::getStringWidth("..") / 2)  , (y + Window::getIconHeight()) - 30);
		x += Window::getIconWidth();
		
	}
	for (int i = 0; i < path->top()->getNbFolder(); i++) {
		string strFolder = path->top()->getFolder(i)->getName();
		if (Window::getWidth() < x + Window::getIconWidth()) {
			x = 0;
			y += Window::getIconHeight();
		}
	
		Window::drawIcon(Icon::FOLDER, x, y, selections->search(i));
		if (Window::getStringWidth(strFolder) > Window::getIconWidth() - Window::getIconWidth() / 5) {
			
			while (Window::getStringWidth(strFolder) > Window::getIconWidth() - Window::getIconWidth() / 5) {
				strFolder.pop_back();
			}
			strFolder += "...";
		}
		Window::drawString(strFolder, x + (Window::getIconWidth() / 2) - (Window::getStringWidth(strFolder) / 2)  , (y + Window::getIconHeight()) - 30);
		x += Window::getIconWidth();
	
	}
	for (int i = 0; i < path->top()->getNbNote(); i++) {
		string strNote = path->top()->getNote(i)->getName();
		if (Window::getWidth() < x + Window::getIconWidth()) {
			x = 0;
			y += Window::getIconHeight();
		}
		Window::drawIcon(Icon::NOTE, x, y, selections->search(getIndex(x, y)));
		if (Window::getStringWidth(strNote) > Window::getIconWidth() - Window::getIconWidth() / 5) {
			
			while (Window::getStringWidth(strNote) > Window::getIconWidth() - Window::getIconWidth() / 5) {
				strNote.pop_back();
			}
			strNote += "...";
		}
		
		Window::drawString(strNote, x + (Window::getIconWidth() / 2) - (Window::getStringWidth(strNote) / 2)  , (y + Window::getIconHeight()) - 30);
		x += Window::getIconWidth();
	}

}

void onWindowClick(const int& x, const int& y, const bool& button, const bool& ctrl) {
	int index = getIndex(x, y);
	//clique gauche
	if (button) {
		
		int indexNote = 0;
		string content = "";
		// sélections multiples
		if (ctrl) {
			if (selections->search(index)) {
				selections->remove(index);
				return;
			}
			else {
				selections->add(index);	
				return;
			}
			
		}
		//Arrangement du titre
		if (index == -1) {
			int texteSize = 0;
			if (path->size() == 2) {
				texteSize = path->top()->getName().length();
			}
			else if (path->size() > 2){
				texteSize = path->top()->getName().length() + 1;
			}
			while (texteSize) {
				title.pop_back();
				texteSize--;
			}
			path->pop();
			
			Window::setTitle(title);
		}
				
		// sélection d'un dossier ou fichier
		if (path->top()->getNbFolder() + path->top()->getNbNote() >= index + 1) {
			selections->clear();
			if (path->top()->getNbFolder() > index) {
				path->push(path->top()->getFolder(index));
				if (path->size() > 2) {

					title += "/";
				}
				title += path->top()->getName();
				Window::setTitle(title);
			}
	
			else if (path->top()->getNbFolder() < index + 1) {
				indexNote = index - path->top()->getNbFolder();
				content = Window::showTextField(path->top()->getNote(indexNote)->getContent());
				path->top()->getNote(indexNote)->setContent(content);
			}
		}
		else {
			selections->clear();
		}
	}
	// clique droit
	else {

		if (index == -1 || path->top()->getNbFolder() + path->top()->getNbNote() < index + 1) {
			selections->clear();
			Window::showMenu(x, y, Menu::NEW_FOLDER | Menu::NEW_NOTE | Menu::SELECT_ALL);
		}
		else if (selections->search(getIndex(x, y)) && selections->size() > 1) {
			Window::showMenu(x, y, Menu::DELETE | Menu::SELECT_ALL);
		}
		else if (path->top()->getNbFolder() + path->top()->getNbNote() >= index + 1 ) {
			selections->clear();
			selections->add(index);
			Window::showMenu(x, y, Menu::NEW_FOLDER | Menu::NEW_NOTE | Menu::RENAME | Menu::DELETE | Menu::ENCODE | Menu::DECODE | Menu::SELECT_ALL);
		}

	}
}

void onMenuClick(const unsigned int& menuItem) {
	string str;
	switch (menuItem) {
	case Menu::NEW_FOLDER:
		str = Window::showTextField();
		if (str != "" && str != " ") {
			for (int i = 0; i < path->top()->getNbFolder(); i++) {
				if (str == path->top()->getFolder(i)->getName()) {
					return;
				}
			}
			
			path->top()->createFolder(str);
			path->top()->sortFolders(0, path->top()->getNbFolder() - 1);
			
		}
		break;
		

	case Menu::NEW_NOTE:
		str = Window::showTextField();
		if (str != "" && str != " ") {
			for (int i = 0; i < path->top()->getNbNote(); i++) {
				if (str == path->top()->getNote(i)->getName()) {
					return;
				}
			}
			path->top()->createNote(str);
			path->top()->sortNotes(0, path->top()->getNbNote() - 1);
			
		}
		break;

	case Menu::RENAME: {
		str = Window::showTextField();
		Queue<int>* selected = new Queue<int>();
		selected->push(selections->first());
		if (str != "" && str != " ") {
			if (path->top()->getNbFolder() >= selected->front() + 1) {
				for (int i = 0; i < path->top()->getNbFolder(); i++) {
					if (str == path->top()->getFolder(i)->getName()) {
						return;
					}
				}	
				path->top()->getFolder(selected->front())->setName(str);
			}
			else if (path->top()->getNbFolder() < selected->front() + 1) {
				for (int i = 0; i < path->top()->getNbNote(); i++) {
					if (str == path->top()->getNote(i)->getName()) {
						return;
					}
				}
				int indexNote = selected->front() - path->top()->getNbFolder();
				path->top()->getNote(indexNote)->setName(str);
			}
				
		}
		delete selected;
		break;
	}

	case Menu::DELETE: {
		Queue<int>* selected = new Queue<int>();
		selected = selections->Traversal(Traversal::Decroissant); 

		while (selected->size()) {
			if (path->top()->getNbFolder() >= selected->front() + 1) {
					
				path->top()->deleteFolder(selected->front());
				selected->pop();
			}
			else if (path->top()->getNbFolder() < selected->front() + 1) {
				int indexNote = selected->front() - path->top()->getNbFolder();
				path->top()->deleteNote(indexNote);
				selected->pop();
			}
			
		}
		selections->clear();
		delete selected;
		break;
	}

	case Menu::ENCODE:
		// TODO : Encoder la note avec la méthode de Huffman
		break;

	case Menu::DECODE:
		// TODO : Décoder la note avec la méthode de Huffman
		break;

	case Menu::SELECT_ALL:
		for (int i = 0; i < path->top()->getNbFolder() + path->top()->getNbNote(); i++) {
			selections->add(i);
		}
		
		break;
	}
}

void onQuit() {
	selections->clear();
	delete selections;
	while (path->size() != 1) {
		path->pop();
	}
	delete path->top();
	path->pop();
	delete path;
}
