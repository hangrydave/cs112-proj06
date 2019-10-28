/* ListTester.cpp defines the test methods for class List<double>.
 * Joel Adams, for CS 112 at Calvin University.
 */


#include "ListTester.h" // ListTester
#include "List.h"       // List<double>
#include <iostream>     // cin, cout
#include <cassert>      // assert()
#include <cstdlib>      // exit()
#include <stdexcept>    // underflow_error
#include <fstream>

using namespace std;

void ListTester::runTests() {
	cout << "Running List<double> tests..." << endl;
	testDefaultConstructor();
	testNodeDefaultConstructor();
	testNodeExplicitConstructor();
	testAppend();
	testDestructor();
	testCopyConstructor();
	testAssignment();
	testInequality();
	testWriteToStream();
	testReadFromFile();
	testGetIndexOf();
	testRemove();
	testInsertBefore();
	testInsertAfter();
	testOstreamOutput();
	cout << "All tests passed!" << endl;
}

void ListTester::testDefaultConstructor() {
	cout << "Testing List<double> default constructor... " << flush;
	List<double> aList;
	assert( aList.mySize == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << "Passed!" << endl;
}

void ListTester::testNodeDefaultConstructor() {
	cout << "Testing Node default constructor... " << flush;
	List<double>::Node aNode;
	assert( aNode.myItem == 0 );
	assert( aNode.myNext == NULL );
	cout << "Passed!" << endl;
}

void ListTester::testNodeExplicitConstructor() {
    cout << "Testing Node explicit constructor... " << flush;
    List<double>::Node n1(11, NULL);
    assert(n1.myItem == 11);
    assert(n1.myNext == NULL);
    cout << " 1 " << flush;

	List<double>::Node *n3 = new List<double>::Node(33, NULL);
	List<double>::Node n2(22, n3);
	assert( n2.myItem == 22 );
	assert( n2.myNext == n3 );
	cout << " 2 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testAppend() {
	cout << "Testing append()... " << flush;
	// empty List<double>
	List<double> aList;
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	try {
		aList.getFirst();
		cerr << "getFirst() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0a " << flush;
	}
	try {
		aList.getLast();
		cerr << "getLast() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0b " << flush;
	}
	// append to empty list
	aList.append(11);
	assert( aList.getSize() == 1 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast == aList.myFirst );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 11 );
	assert( aList.myFirst->myNext == NULL );
	cout << " 1 " << flush;
	// append to a list containing 1 Item
	aList.append(22);
	assert( aList.getSize() == 2 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast != NULL );
	assert( aList.myFirst != aList.myLast );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 22 );
	assert( aList.myFirst->myNext != NULL );
	assert( aList.myLast->myNext == NULL );
	cout << " 2 " << flush;
	// append to a list containing 2 Items
	aList.append(33);
	assert( aList.getSize() == 3 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast != NULL );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 33 );
	assert( aList.myFirst->myNext->myItem == 22 );
	assert( aList.myLast->myNext == NULL );
	cout << " 3 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testDestructor() {
	cout << "Testing destructor... " << flush;
	List<double> aList;
	aList.~List<double>();
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << " 1 " << flush;

	aList.append(11);
	aList.append(22);
	aList.append(33);
	aList.~List<double>();
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << " 2 " << flush;
	cout << "Passed!  But double-check for memory leaks!" << endl;
}

void ListTester::testCopyConstructor() {
	cout << "Testing copy constructor... " << flush;
	// copy empty list
	List<double> list1;
	List<double> list2(list1);
	assert( list2.getSize() == 0 );
	assert( list2.myFirst == NULL );
	assert( list2.myLast == NULL );
	cout << " 1 " << flush;

	// copy nonempty list
	List<double> list3;
	list3.append(11);
	list3.append(22);
	list3.append(33);
	List<double> list4(list3);
	assert( list4.getSize() == 3 );
	assert( list4.getFirst() == 11 );
	assert( list4.getLast() == 33 );
	assert( list4.myFirst->myNext->myItem == 22 );
	assert( list4.myFirst != list3.myFirst );
	assert( list4.myLast != list3.myLast );
	cout << " 2 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testAssignment() {
	cout << "Testing assignment... " << flush;
	// empty to empty assignment
	List<double> list1;
	List<double> list2;
	list2 = list1;
	assert( list2.getSize() == 0 );
	assert( list2.myFirst == NULL );
	assert( list2.myLast == NULL );
	cout << " 1 " << flush;

	// non-empty to empty assignment
	List<double> list3;
	list3.append(11);
	list3.append(22);
	list3.append(33);
	List<double> list4;
	list4 = list3;
	assert( list4.getSize() == 3 );
	assert( list4.getFirst() == 11 );
	assert( list4.getLast() == 33 );
	assert( list4.myFirst->myNext->myItem == 22 );
      // check that nodes are distinct
	assert( list4.myFirst != list3.myFirst );
	assert( list4.myFirst->myNext != list3.myFirst->myNext );
	assert( list4.myLast != list3.myLast );
	cout << " 2 " << flush;

	// equal-sized non-empty to non-empty assignment
	List<double> list5;
	list5.append(44);
	list5.append(55);
	list5.append(66);
	list5 = list3;
	assert( list5.getSize() == 3 );
	assert( list5.getFirst() == 11 );
	assert( list5.getLast() == 33 );
	assert( list5.myFirst->myNext->myItem == 22 );
      // check that nodes are distinct
	assert( list5.myFirst != list3.myFirst );
	assert( list5.myFirst->myNext != list3.myFirst->myNext );
	assert( list5.myLast != list3.myLast );
	cout << " 3 " << flush;

	// empty to non-empty assignment
	List<double> list6;
	list6.append(44);
	list6.append(55);
	list6.append(66);
	List<double> list7;
	list6 = list7;
	assert( list6.getSize() == 0 );
	assert( list6.myFirst == NULL );
	assert( list6.myLast == NULL );
	cout << " 4 " << flush;

	// unequal-sized non-empty to non-empty assignment
	List<double> list8;
	list8.append(44);
	list8.append(55);
	list8.append(66);
	list8.append(77);
	list8 = list3;
	assert( list8.getSize() == 3 );
	assert( list8.getFirst() == 11 );
	assert( list8.getLast() == 33 );
	assert( list8.myFirst->myNext->myItem == 22 );
      // check that nodes are distinct
	assert( list8.myFirst != list3.myFirst );
	assert( list8.myFirst->myNext != list3.myFirst->myNext );
	assert( list8.myLast != list3.myLast );
	cout << " 5 " << flush;

	// assignment chaining
	List<double> list9;
	list9.append(44);
	list9.append(55);
	list9.append(66);
	list9.append(77);
	List<double> list10;
    list10 = (list9 = list8);
	assert( list10.getSize() == 3 );
	assert( list10.getFirst() == 11 );
	assert( list10.getLast() == 33 );
	assert( list10.myFirst->myNext->myItem == 22 );
	cout << " 6 " << flush;

	// self-assignment (stupid, but possible)
	List<double> list11;
	list11.append(11);
	list11.append(22);
	list11.append(33);
	list11 = list11;
	assert( list11.getSize() == 3 );
	assert( list11.getFirst() == 11 );
	assert( list11.getLast() == 33 );
	assert( list11.myFirst->myNext->myItem == 22 );
	cout << " 7 " << flush;

	cout << "Passed!  But double-check for memory leaks!" << endl;
}

void ListTester::testInequality() {
    cout << "Testing inequality..." << flush;

    // test different elements
    List<double> list1;
    list1.append(1);
    list1.append(2);
    list1.append(3);
    List<double> list2;
    list2.append(3);
    list2.append(2);
    list2.append(1);
    assert(list1 != list2);
    cout << " 0 " << flush;

    // test same elements
    List<double> list3;
    list3.append(21);
    list3.append(22);
    list3.append(23);
    List<double> list4;
    list4.append(21);
    list4.append(22);
    list4.append(23);
    assert(!(list3 != list4));
    cout << " 1 " << flush;

    // test different lengths
    List<double> list5;
    list5.append(1);
    list5.append(1);
    List<double> list6;
    list6.append(1);
    assert(list5 != list6);
    cout << " 2 " << flush;

    // test inequality check against self
    List<double> list7;
    assert(!(list7 != list7));
    cout << " 3 " << flush;
    cout << "Passed!" << endl;
}

void ListTester::testWriteToStream() {
    cout << "Testing writing to a stream..." << flush;
    
    List<double> list1;
    list1.append(1);
    list1.append(2);
    list1.append(3);
    
    // test writing to a stream with a tab character as delimiter
    ofstream fout1("list_writeTo_output1.txt");
    assert(fout1.is_open());
    list1.writeTo(fout1, '\t');
    fout1.close();

    ifstream fin1("list_writeTo_output1.txt");
    assert(fin1.is_open());
    for (unsigned i = 0; i < list1.mySize; i++) {
        double value;
        fin1 >> value;
        assert(value == i + 1);
    }
    cout << " 0 " << flush;

    // test writing to a stream with a newline character as delimiter
    ofstream fout2("list_writeTo_output2.txt");
    assert(fout2.is_open());
    list1.writeTo(fout2, '\n');
    fout2.close();

    ifstream fin2("list_writeTo_output2.txt");
    assert(fin2.is_open());
    for (unsigned i = 0; i < list1.mySize; i++) {
        double value;
        fin2 >> value;
        assert(value == i + 1);
    }
    cout << " 1 " << flush;

    cout << "Passed! See list_writeTo_output.txt for values..." << endl;
}

void ListTester::testReadFromFile() {
    cout << "Testing reading from a file..." << flush;

    // read from a file with three values
    List<double> list1;
    list1.readFrom("list_readFrom_input1.txt");

    double counter = 1;
    for (List<double>::Node* next = list1.myFirst; next; next = next->myNext) {
        assert(next->myItem == counter);
        ++counter;
    }
    cout << " 0 " << flush;

    // read from two files, one of which has 2 values and the other having 3
    List<double> list2;
    list2.readFrom("list_readFrom_input2.txt");
    list2.readFrom("list_readFrom_input3.txt");

    counter = 1;
    for (List<double>::Node* next = list2.myFirst; next; next = next->myNext) {
        assert(next->myItem == counter);
        ++counter;
    }
    cout << " 1 " << flush;

    // read from a file with no elements
    List<double> list3;
    list3.readFrom("list_readFrom_input4.txt");
    assert(list3.myFirst == nullptr && list3.myLast == nullptr);
    cout << " 2 " << flush;

    cout << "Passed!" << endl;
}

void ListTester::testGetIndexOf() {
    cout << "Testing getting the index of an item..." << flush;

    // get the index of an item that is in the list
    List<double> list1;
    list1.append(1);
    list1.append(2);
    list1.append(3);
    unsigned index1 = list1.getIndexOf(2);
    assert(index1 == 1);
    cout << " 0 " << flush;

    // get the index of an item that is not in the list
    List<double> list2;
    list2.append(33);
    list2.append(44);
    list2.append(66);
    unsigned index2 = list2.getIndexOf(55);
    assert(index2 == -1);
    cout << " 1 " << flush;

    cout << "Passed!" << endl;
}

void ListTester::testRemove() {
    cout << "Testing removing an item..." << flush;

    // remove an item in the middle of the list
    List<double> list1;
    list1.append(1);
    list1.append(2);
    list1.append(3);
    double removed = list1.remove(1);
    assert(removed == 2);
    assert(list1.mySize == 2);
    for (List<double>::Node* next = list1.myFirst; next; next = next->myNext) {
        assert(next->myItem != 2);
    }
    cout << " 0 " << flush;

    // remove an item using a very large index
    List<double> list2;
    list2.append(1);
    list2.append(2);
    list2.append(3);
    removed = list2.remove(400);
    assert(removed == 3);
    assert(list2.mySize == 2);
    for (List<double>::Node* next = list2.myFirst; next; next = next->myNext) {
        assert(next->myItem != 3);
    }
    cout << " 1 " << flush;

    // remove an item using a very small index
    List<double> list3;
    list3.append(1);
    list3.append(2);
    list3.append(3);
    removed = list3.remove(-99);
    assert(removed == 1);
    assert(list3.mySize == 2);
    for (List<double>::Node* next = list3.myFirst; next; next = next->myNext) {
        assert(next->myItem != 1);
    }
    cout << " 2 " << flush;

    // remove an item from a list with two items
    List<double> list4;
    list4.append(1);
    list4.append(5);
    removed = list4.remove(0);
    assert(removed == 1);
    assert(list4.mySize == 1);
    assert(list4.myFirst == list4.myLast);
    for (List<double>::Node* next = list4.myFirst; next; next = next->myNext) {
        assert(next->myItem != 1);
    }
    cout << " 3 " << flush;

    // remove an item from a list with one item
    List<double> list5;
    list5.append(1);
    removed = list5.remove(0);
    assert(removed == 1);
    assert(list5.mySize == 0);
    assert(list5.myFirst == nullptr);
    assert(list5.myLast == nullptr);
    cout << " 4 " << flush;

    // remove an item from a list with no items
    List<double> list6;
    try {
        removed = list6.remove(0);
        assert(false); // we should not be here
    } catch (out_of_range& error) {
        // the remove method successfully exited when the list had no elements
    }
    assert(list6.mySize == 0);
    cout << " 5 " << flush;

    cout << "Passed!" << endl;
}

void ListTester::testInsertAfter() {
    cout << "Testing insertAfter()... " << flush;

    // insert in empty list
    List<double> aList;
    bool successfullyInserted = aList.insertAfter(1, 11);
    assert(!successfullyInserted);
    assert(aList.getSize() == 0);
    assert(aList.myFirst == nullptr);
    assert(aList.myLast == nullptr);
    cout << " 1 " << flush;

    // insert in a list containing 1 Item
    aList.append(22);
    successfullyInserted = aList.insertAfter(22, 28);
    assert(successfullyInserted);
    assert(aList.mySize == 2);
    assert(aList.myFirst->myItem == 22);
    assert(aList.myLast->myItem == 28);
    cout << " 2 " << flush;

    // insert in a list containing 2 Items
    // 22 28
    successfullyInserted = aList.insertAfter(22, 33);
    // 22 33 28
    assert(successfullyInserted);
    assert(aList.getSize() == 3);
    assert(aList.myFirst->myNext->myItem == 33);
    assert(aList.myFirst->myItem == 22);
    assert(aList.myLast->myItem == 28);
    cout << " 3 " << flush;

    // insert in a list containing 3 items but not the specified item
    successfullyInserted = aList.insertAfter(51, 28);
    assert(!successfullyInserted);
    assert(aList.mySize == 3);
    assert(aList.myFirst->myItem == 22);
    assert(aList.myLast->myItem == 28);
    cout << " 4 " << flush;
    cout << "Passed!" << endl;
}

void ListTester::testInsertBefore() {
    cout << "Testing insertBefore()... " << flush;

    // insert in empty list
    List<double> aList;
    bool successfullyInserted = aList.insertBefore(1, 11);
    assert(!successfullyInserted);
    assert(aList.getSize() == 0);
    assert(aList.myFirst == nullptr);
    assert(aList.myLast == nullptr);
    cout << " 1 " << flush;

    // insert in a list containing 1 Item
    aList.append(22);
    // 22
    successfullyInserted = aList.insertBefore(22, 28);
    // 28 22
    assert(successfullyInserted);
    assert(aList.mySize == 2);
    assert(aList.myFirst->myItem == 28);
    assert(aList.myLast->myItem == 22);
    cout << " 2 " << flush;

    // insert in a list containing 2 Items
    // 28 22
    successfullyInserted = aList.insertBefore(22, 33);
    // 28 33 22
    assert(successfullyInserted);
    assert(aList.getSize() == 3);
    assert(aList.myFirst->myNext->myItem == 33);
    assert(aList.myFirst->myItem == 28);
    assert(aList.myLast->myItem == 22);
    cout << " 3 " << flush;

    // insert in a list containing 3 items but not the specified item
    successfullyInserted = aList.insertBefore(51, 28);
    assert(!successfullyInserted);
    assert(aList.mySize == 3);
    assert(aList.myFirst->myItem == 28);
    assert(aList.myLast->myItem == 22);
    cout << " 4 " << flush;
    cout << "Passed!" << endl;
}

void ListTester::testOstreamOutput() {
    cout << "Testing the << operator..." << flush;

    List<double> list1;
    list1.append(1);
    list1.append(2);
    list1.append(3);

    ofstream fout1("list_output_operator.txt");
    assert(fout1.is_open());
    fout1 << list1;
    fout1.close();

    ifstream fin1("list_output_operator.txt");
    assert(fin1.is_open());
    for (unsigned i = 0; i < 6; i++) {
        if (i % 2 == 0) {
            // in this case, it should be a =
            char value;
            fin1 >> value;
            assert(value == '=');
        } else {
            // in this case, it should be a number
            double value;
            fin1 >> value;

            // if it's an odd number, then integer division makes i / 2 however many 2s are inside i. Add 1, and we're good.
            assert(value == (i / 2) + 1);
        }
    }

    cout << "Passed! See list_output_operator.txt for values..." << endl;
}
