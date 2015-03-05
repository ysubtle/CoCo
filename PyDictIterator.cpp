#include "PyDictIterator.h"
#include <string>
using namespace std;

PyDictIterator::PyDictIterator() {

}

PyDictIterator::~PyDictIterator() {

}

PyType* PyDictIterator::getType() {
	return PyTypes[PyDictIteratorType];
}

string PyDictIterator::toString() {
	ostringstream s;

	s << "<dict_iterator object at " << this << ">";

	return s.str();
}

PyObject* PyDictIterator::__iter__(vector<PyObject*>* args) {

}

PyObject* PyListIterator::__next__(vector<PyObject*>* args) {

}