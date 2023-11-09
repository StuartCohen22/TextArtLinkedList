#include <iostream>
#include <Windows.h>
#include "Definitions.h"
#include <fstream>
using namespace std;


Node* newCanvas()
{
	// TODO: Write the code for the function

	Node* current = new Node;
	current->next = NULL;

	initCanvas(current->item);

	return current;
}


Node* newCanvas(Node* oldNode)
{
	// TODO: Write the code for the function

	Node* newNode = new Node;
	newNode->next = NULL;

	copyCanvas(newNode->item, oldNode->item);

	return newNode;
}


void play(List& clips)
{
	// Check if there are at least 2 clips in the animation
	if (clips.count < 2)
	{
		return;
	}

	// Start playing the animation using recursive function
	clearLine(MAXROWS + 1, 90);  // clear the bottom line of the screen
	clearLine(MAXROWS + 2, 90);
	gotoxy(MAXROWS + 1, 0);

	cout << "Hold <ESC> to stop\t" << "Clip: ";

	// Wait for the user to press the Escape key
	while (!(GetKeyState(VK_ESCAPE) & 0x8000)) {
		playRecursive(clips.head, clips.count);
		// Sleep(100);  // pause for 100 milliseconds
	}
}


void playRecursive(Node* head, int count)
{
	// Base case: if the head pointer is null, return
	if (head == nullptr)
	{
		return;
	}

	// recurse to the next node
	playRecursive(head->next, count - 1);
	// display the current clip
	displayCanvas(head->item);

	// go to the bottom-left corner of the screen

	gotoxy(MAXROWS + 1, 32);

	cout << "           ";

	gotoxy(MAXROWS + 1, 32);

	// print the current clip number
	cout << count;

	gotoxy(MAXROWS + 1, 40);

	// pause for 100 milliseconds
	Sleep(100);

}


void addUndoState(List& undoList, List& redoList, Node*& current)
{
	// TODO: Write the code for the function

	Node* undoNode = new Node;
	copyCanvas(undoNode->item, current->item);

	addNode(undoList, undoNode);

	// undoList.count++;

	deleteList(redoList);
}


void restore(List& undoList, List& redoList, Node*& current)
{
	// TODO: Write the code for the function

	if (undoList.count == 0)
		return;

	addNode(redoList, current);

	current = removeNode(undoList);
}


void addNode(List& list, Node* nodeToAdd)
{
	// TODO: Write the code for the function

	//set the next pointer of the new node to the current head of the list
	nodeToAdd->next = list.head;

	//set the head of the list to the new node
	list.head = nodeToAdd;

	// increment the count of list
	list.count++;
}


Node* removeNode(List& list)
{
	// TODO: Write the code for the function

	if (list.head == NULL)
		return NULL;

	// save a pointer to the first node in the list
	Node* removedNode = list.head;

	// set the head of the list to the next node
	list.head = removedNode->next;

	// decrement the count of items in the list
	list.count--;

	return removedNode;
}


void deleteList(List& list)
{
	// TODO: Write the code for the function

	while (list.head != NULL)
	{
		Node* temp = list.head->next;
		delete list.head;
		list.head = temp;
	}

	list.count = 0;
}


bool loadClips(List& clips, char filename[])
{
	// char array to hold the full filepath
	char filePath[FILENAMESIZE];

	deleteList(clips);

	// keep track of # of files
	int num = 1;

	// attach the file path to the beginning of the file name entered by user
	snprintf(filePath, FILENAMESIZE, "SavedFiles\\%s", filename);

	// a copy of filename that will have edits done
	char fileNameCopy[FILENAMESIZE];
	snprintf(fileNameCopy, FILENAMESIZE, filePath);
	snprintf(fileNameCopy, FILENAMESIZE, "%s-%d.txt", filePath, num);

	Node* current = newCanvas();

	/*
	ifstream clipFile;
	clipFile.open(fileNameCopy);
	*/

	// clipsFile.is_open()

	/*
	if (!clipFile.is_open())
	{
		return false;
	}
	*/

	while (loadCanvas(current->item, fileNameCopy))
	{
		addNode(clips, current);
		current = newCanvas();

		snprintf(fileNameCopy, FILENAMESIZE, " ");
		num++;
		snprintf(fileNameCopy, FILENAMESIZE, "SavedFiles\\%s-%d.txt", filename, num);

	}

	while (current != NULL)
	{
		Node* temp = current;
		current = current->next;
		delete temp;
	}

	if (clips.head == NULL)
	{
		return false;
	}

	cout << "Clips Loaded!\n";
	system("pause");

	clearLine(MAXROWS + 1, 90);
	clearLine(MAXROWS + 2, 90);
	clearLine(MAXROWS + 3, 90);

	// clipFile.close();

	return true;
}


bool saveClips(List& clips, char filename[])
{
	// TODO: Write the code for the function

	// char array to hold the full filepath
	char fileNameCopy[FILENAMESIZE];

	// keep track of # of files
	int num = 1;

	/*
	// a copy of filename that will have edits done
	char fileNameCopy[FILENAMESIZE];
	snprintf(fileNameCopy, FILENAMESIZE, filePath);
	snprintf(fileNameCopy, FILENAMESIZE, "%s-%d.txt", filePath, num);
	*/

	// copy of list of clips
	List copy = clips;

	Node* currentClip = copy.head;
	Node* next1 = NULL;
	Node* previousNode = NULL;

	while (currentClip != NULL)
	{
		next1 = currentClip->next;
		currentClip->next = previousNode;
		previousNode = currentClip;
		currentClip = next1;
	}
	copy.head = previousNode;

	if (copy.head == NULL)
	{
		return false;
	}

	Node* current = copy.head;
	Node* next2 = current->next;

	while (current != NULL)
	{
		// creates the full file name
		snprintf(fileNameCopy, FILENAMESIZE, "%s-%d.txt", filename, num);

		if (saveCanvas(current->item, fileNameCopy))
		{
			next2 = current->next;
			current = next2;
		}
		else
		{
			return false;
		}

		snprintf(fileNameCopy, FILENAMESIZE, " ");
		num++;
	}

	deleteList(copy);
	return true;
}