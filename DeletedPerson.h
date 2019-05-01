#pragma once

#include <string>
#include <typeinfo>

#include "Manips.h"
#include "BST.h"
#include "Person.h"
#include "Student.h"
#include "Faculty.h"

class DeletedPerson: public Manips
{
public:
    DeletedPerson();
    ~DeletedPerson();
    DeletedPerson(Person *myP, BST<Person*>* aT, BST<Person*> *oT, DoublyLinkedList<int>* IDs);
    DeletedPerson(Person *myP, BST<Person*>* aT, BST<Person*> *oT);
    void recFacultyID(TreeNode<Person*>* node);
    void undoOperation(); // Delete
    void redoOperation();

// private:
    Person *affectedPerson;
    BST<Person*>* affectedTree; // Tree that contains the person
    BST<Person*>* otherTree; // The other tree
    DoublyLinkedList<int>* facultyIDs;
};