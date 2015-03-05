#include "PyDictIterator.h"
#include <string>
using namespace std;

PyDictIterator::PyDictIterator() {
	this->index = 0;
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

PyObject* PyListIterator::__next__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return lst->getVal(index++);
}