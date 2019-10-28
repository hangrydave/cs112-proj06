/*
 * This class acts as a singly linked list.
 * Created by dar23 on 10/8/19.
 */

#ifndef LAB05_LIST_H
#define LAB05_LIST_H

#include <stdexcept>
#include <iostream>
#include <fstream>

using namespace std;

template<class Item>
class List {
private:
    friend class ListTester;
    struct Node {
        Item myItem;
        Node* myNext;
        Node();
        Node(Item item, Node* next);
        virtual ~Node();
    };
    unsigned mySize;
    Node* myFirst;
    Node* myLast;
    void deepCopy(const List<Item>& list);

    /*
     * Output the items of a List to an ostream separated by =.
     * @param: os, the ostream to output the items to.
     * @param: list, the list whose items will be outputted.
     * Returns: the ostream that has had the list's items outputted to it.
     */
    friend ostream& operator <<(ostream& os, const List<Item>& list) {
        for (Node* node = list.myFirst; node; node = node->myNext) {
            os << '=' << node->myItem;
        }
        return os;
    }
public:
    List();
    List(const List<Item>& list);
    virtual ~List();
    unsigned getSize() const;
    Item getFirst() const;
    Item getLast() const;
    void append(const Item& item);
    List<Item>& operator =(const List<Item>& list);
    bool operator !=(const List<Item>& list) const;
    void writeTo(ostream& ostream, char delimiter = '\t') const;
    void readFrom(const string& fileName);
    unsigned getIndexOf(const Item& item) const;
    Item remove(int index);
    bool insertAfter(const Item& itemBefore, const Item& newItem);
    bool insertBefore(const Item& itemAfter, const Item& newItem);
};


/*
 * Implicit List constructor.
 * Postcondition: The size of this List is 0 and there are no Nodes.
 */
template<class Item>
List<Item>::List() {
    mySize = 0;
    myFirst = nullptr;
    myLast = nullptr;
}

/*
 * List copy constructor.
 * @param: list, a List to deep copy.
 * Postcondition: This List is a deep copy of the passed in List.
 */
template<class Item>
List<Item>::List(const List<Item>& list) {
    deepCopy(list);
}

/*
 * Destructor of a List.
 * Postcondition: The size of this List is 0 and each node has been deallocated.
 */
template<class Item>
List<Item>::~List() {
    mySize = 0;
    delete myFirst; // this will recursively call destructors on each of the nodes
    myFirst = nullptr;
    myLast = nullptr;
}

/*
 * Implicit constructor of a Node.
 * Postcondition: This Node contains an Item with a default value and a null next Node pointer.
 */
template<class Item>
List<Item>::Node::Node() {
    myItem = Item();
    myNext = nullptr;
}

/*
 * Explicit constructor of a Node.
 * Postcondition: This Node contains a specified Item and a reference to another Node as the next Node.
 */
template<class Item>
List<Item>::Node::Node(Item item, List<Item>::Node *next) {
    myItem = item;
    myNext = next;
}

/*
 * Destructor of a Node.
 * Postcondition: This Node and all of the following Nodes are deallocated.
 */
template<class Item>
List<Item>::Node::~Node() {
    delete myNext;
    myNext = nullptr;
}

/*
 * Get the size of this List.
 * Returns: The size of this List.
 */
template<class Item>
unsigned List<Item>::getSize() const {
    return mySize;
}

/*
 * Get the first Item in this List.
 * Returns: The Item at the beginning of this List.
 */
template<class Item>
Item List<Item>::getFirst() const {
    if (myFirst == nullptr || mySize == 0)
        throw underflow_error("no nodes in list");

    return myFirst->myItem;
}

/*
 * Get the last Item in this List.
 * Returns: The Item at the end of this List.
 */
template<class Item>
Item List<Item>::getLast() const {
    if (myLast == nullptr || mySize == 0)
        throw underflow_error("no nodes in list");

    return myLast->myItem;
}

/*
 * Append an Item to this List.
 * @param: item, an Item to append to the end of this List.
 * Postcondition: This List has had the passed in Item appended to the end.
 */
template<class Item>
void List<Item>::append(const Item& item) {
    mySize++;
    Node* newNode = new Node(item, nullptr);
    if (myLast != nullptr) {
        myLast->myNext = newNode;
    } else {
        myFirst = newNode;
    }
    myLast = newNode;
}

/*
 * Assign another List to this one.
 * @param: list, a List to copy the values of.
 * Returns: This List with identical values to those of the one passed in.
 * Postcondition: This List is identical in values to the one passed in.
 */
template<class Item>
List<Item>& List<Item>::operator=(const List<Item>& list) {
    if (&list == this)
        return *this;

    delete myFirst;

    deepCopy(list);
    return *this;
}

/*
 * Make this List a deep copy of another List.
 * @param: list, a list to create a deep copy of.
 * Postcondition: This List has identical values to those of the one passed in.
 */
template<class Item>
void List<Item>::deepCopy(const List<Item>& list) {
    myFirst = nullptr;
    myLast = nullptr;
    mySize = 0;

    for (Node* node = list.myFirst; node; node = node->myNext) {
        append(node->myItem);
    }
}

/*
 * Check if this List is inequal to another.
 * @param: list, a list to check for inequality against.
 * Returns: True if inequal, false if not.
 */
template<class Item>
bool List<Item>::operator !=(const List<Item>& list) const {
    if (this == &list)
        return false;

    if (mySize != list.mySize)
        return true;

    Node* node = myFirst;
    Node* otherNode = list.myFirst;
    while (node) {
        if (node->myItem != otherNode->myItem)
            return true;

        node = node->myNext;
        otherNode = otherNode->myNext;
    }

    return false;
}

/*
 * Write values from this List to an ostream.
 * @param: ostream, an ostream to write values to.
 * @param: delimiter, a char delimiter to write in between the elements.
 */
template<class Item>
void List<Item>::writeTo(ostream& ostream, char delimiter) const {
    for (Node* node = myFirst; node; node = node->myNext) {
        ostream << node->myItem << delimiter;
    }
    ostream << flush;
}

/*
 * Read values from a file into this List.
 * @param: fileName, the name of the file to read from.
 * Postcondition: This List contains the values inside the specified file.
 */
template<class Item>
void List<Item>::readFrom(const string& fileName) {
    ifstream fileInput(fileName);

    // This is here because I was getting 0 from an empty file, sourced from https://stackoverflow.com/questions/2390912/checking-for-an-empty-file-in-c
    bool isEmpty = fileInput.peek() == ifstream::traits_type::eof();
    if (isEmpty)
        return;

    Item item;
    while (fileInput && !fileInput.eof()) {
        fileInput >> item;
        append(item);
    }
}

/*
 * Get the index of an Item in this List.
 * @param: item, an item to find the index of.
 * @return The index where the Item is, or -1 if the Item is not in this List.
 */
template<class Item>
unsigned List<Item>::getIndexOf(const Item& item) const {
    unsigned index = 0;
    for (Node* node = myFirst; node; node = node->myNext) {
        if (node->myItem == item)
            return index;

        ++index;
    }
    return -1;
}

/*
 * Remove and return an Item at a specified index from the List.
 * @param: index, the index to delete the Node at.
 * Returns: The Item that was at the specified index.
 * Postcondition: This List no longer contains the Item that was at that index, and the first and last Nodes have been updated.
 */
template<class Item>
Item List<Item>::remove(int index) {
    if (mySize == 0)
        throw out_of_range("list is empty");

    // fit index to range
    if (index < 0)
        index = 0;
    else if (index > mySize - 1)
        index = mySize - 1;

    // find the specified Node and the ones directly in front and behind
    unsigned counter = 0;
    Node* precedingNode = nullptr;
    Node* nodeAtIndex = nullptr;
    Node* nextNode = nullptr;
    for (Node* node = myFirst; node; node = node->myNext) {
        if (counter == index - 1) {
            precedingNode = node;
        } else if (counter == index) {
            nodeAtIndex = node;
        } else if (counter == index + 1) {
            nextNode = node;
            break;
        }
        counter++;
    }

    // store the item and delete the Node
    Item item = nodeAtIndex->myItem;
    nodeAtIndex->myNext = nullptr;
    delete nodeAtIndex;

    if (mySize == 1) { // element to delete is both the first and last
        myFirst = nullptr;
        myLast = nullptr;
    }

    if (index == 0) { // first Node
        myFirst = nextNode;
    } else if (index == mySize - 1) { // last Node
        precedingNode->myNext = nullptr;
        myLast = precedingNode;
    } else { // not first or last Node
        precedingNode->myNext = nextNode;
    }

    mySize--;
    return item;
}

/*
 * Insert an item after an already existing item.
 * @param: itemBefore, the item to put an item after.
 * @param: newItem, the item to put after itemBefore.
 * Returns: true if successful, false if itemBefore was not in the array.
 * Postcondition: This List contains newItem after itemBefore, or there have been no changes if itemBefore was not in this List.
 */
template<class Item>
bool List<Item>::insertAfter(const Item& itemBefore, const Item& newItem) {
    if (mySize == 0)
        return false;

    // If we are putting an item after the last item, then we shouldn't bother looping through every node.
    if (itemBefore == myLast->myItem) {
        myLast = myLast->myNext = new Node(newItem, nullptr);
        ++mySize;
        return true;
    }

    for (Node* node = myFirst; node; node = node->myNext) {
        if (node->myItem == itemBefore) {
            if (node->myNext == nullptr)
                myLast = node->myNext = new Node(newItem, nullptr);
            else
                node->myNext = new Node(newItem, node->myNext);

            ++mySize;
            return true;
        }
    }

    return false;
}

/*
 * Insert an item before an already existing item.
 * @param: itemAfter, the item to put an item before.
 * @param: newItem, the item to put before itemAfter.
 * Returns: true if successful, false if itemAfter was not in the array.
 * Postcondition: This List contains newItem before itemAfter, or there have been no changes if itemAfter was not in this List.
 */
template<class Item>
bool List<Item>::insertBefore(const Item& itemAfter, const Item& newItem) {
    if (mySize == 0)
        return false;

    Node* previousNode = nullptr;
    for (Node* node = myFirst; node; node = node->myNext) {
        if (node->myItem == itemAfter) {
            if (previousNode != nullptr)
                previousNode->myNext = new Node(newItem, node);
            else
                myFirst = new Node(newItem, node);

            ++mySize;
            return true;
        }
        previousNode = node;
    }

    return false;
}

#endif //LAB05_LIST_H
