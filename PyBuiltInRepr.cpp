#include "PyBuiltInRepr.h"
#include "PyObject.h"
#include "PyException.h"

#include <vector>
#include <sstream>
using namespace std;

PyBuiltInRepr::PyBuiltInRepr() : PyCallable() {
}

PyBuiltInRepr::PyBuiltInRepr(const PyBuiltInRepr& orig) {
}

PyBuiltInRepr::~PyBuiltInRepr() {
}

PyType* PyBuiltInRepr::getType() {
    return PyTypes[PyBuiltInType];
}

PyObject* PyBuiltInRepr::__call__(vector<PyObject*>* args) {
    PyObject* x;
    ostringstream msg;
    
    if (args->size() != 1) {
        msg << "TypeError expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str(),__FILE__,__LINE__);  
    }

    x = (*args)[0];
    
    vector<PyObject*>* callArgs = new vector<PyObject*>();
    
    return x->callMethod("__repr__",callArgs);
}

string PyBuiltInRepr::toString() {
    return "repr";
}