#pragma once

#include <string>
#include <typeinfo>

#include "Manips.h"
#include "BST.h"
#include "Person.h"
#include "Student.h"
#include "Faculty.h"

class InsertedPerson: public Manips
{
public:
    InsertedPerson();
    InsertedPerson(Person *myP, BST<Person*>* aT, BST<Person*>* oT, DoublyLinkedList<int>* IDs);
    InsertedPerson(Person *myP, BST<Person*>* aT, BST<Person*> *oT);
    void recFacultyID(TreeNode<Person*>* node);
    void undoOperation(); // Delete
    void redoOperation();

private:
    Person *affectedPerson;
    BST<Person*>* affectedTree; // Tree that contains the person
    BST<Person*>* otherTree; // The other tree
    DoublyLinkedList<int>* facultyIDs;
};

InsertedPerson::InsertedPerson()
{

}

InsertedPerson::InsertedPerson(Person *myP, BST<Person*> *aT, BST<Person*> *oT, DoublyLinkedList<int>* IDs)
    :affectedPerson(myP), affectedTree(aT), otherTree(oT)
{
    facultyIDs = IDs;
}
InsertedPerson::InsertedPerson(Person *myP, BST<Person*> *aT, BST<Person*> *oT)
    :affectedPerson(myP), affectedTree(aT), otherTree(oT)
{
    if(!myP->isStudent)
    {
        facultyIDs = new DoublyLinkedList<int>;
        recFacultyID(affectedTree->root);
    }

}
void InsertedPerson::recFacultyID(TreeNode<Person*>* node)
{
    if(node == NULL) return;
    recFacultyID(node->left);
    facultyIDs->insertFront(node->key);
    recFacultyID(node->right);
}

void InsertedPerson::undoOperation() // Oposite of action done
{
    if(affectedPerson->isStudent)
    {
        // If it's a student being edited
        Student* tempStud = dynamic_cast<Student*> (affectedPerson);
        Faculty* tempFac = dynamic_cast<Faculty*> (otherTree->findKey(tempStud->advisorID));

        tempFac->removeAdvisee(tempStud->id);
    }
    else
    {
        // if it's faculty being edited
        Faculty* tempFac = dynamic_cast<Faculty*> (affectedPerson);
        ListNode<int>* current = tempFac->advisees.getHead();
        int numberOfFaculty = facultyIDs->getSize();
        while(current!=NULL && !(otherTree->isEmpty()))
        {

            Student* tempStud = dynamic_cast<Student*> (otherTree->findKey(current->data));
            cout << "here" << endl;


            cout << tempStud->advisorID << endl;

            tempStud->advisorID = facultyIDs->index(rand()%numberOfFaculty);
            cout << "here" << endl;


            current = current->next;
        }
    }
    affectedTree->deleteR(affectedPerson->id);
}

void InsertedPerson::redoOperation() // Action done
{
    if(affectedPerson->isStudent)
    {
        // If it's a student being edited

        // Insert the student and change the faculty to have them in their list

        Student* tempStud = dynamic_cast<Student*> (affectedPerson);

        Faculty* tempFac = dynamic_cast<Faculty*> (otherTree->findKey(tempStud->advisorID));

        tempFac->AddAdvisee((tempStud->id));
    }
    else
    {
        // if it's faculty being edited


        // Insert the faculty and give them back all of their students

        Faculty* tempFac = dynamic_cast<Faculty*> (affectedPerson);

        ListNode<int>* current = tempFac->advisees.getHead();

        while(current!=NULL && !(otherTree->isEmpty()))
        {

            Student* tempStud = dynamic_cast<Student*> (otherTree->findKey(current->data));


            tempStud->advisorID = tempFac->id;


            current = current->next;
        }

    }

    affectedTree->insert(affectedPerson->id, affectedPerson);
}
