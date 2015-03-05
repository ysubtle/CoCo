#include "PyDictIterator.h"
#include <string>
using namespace std;

PyDictIterator::PyDictIterator(PyObject* map) {
	this->index = 0;
	this->map = map;
	this->it = map.begin();
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
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return this;
}

PyObject* PyDictIterator::__next__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    PyObject* value = it->second;
    it++;
    return value;
}