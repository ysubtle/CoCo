/* 
 * File:   PyTuple.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on March 7, 2013, 11:26 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * See the associated header file for a description of the purpose of this 
 * class. Implementation details are provided here. Read below for 
 * any specific details. 
 * 
 */

#include "PyTuple.h"
#include "PyTupleIterator.h"
#include "PyException.h"
#include "PyInt.h"
#include "PyStr.h"
#include "PyType.h"
#include "PyBool.h"
#include <sstream>
using namespace std;

PyTuple::PyTuple(vector<PyObject*>* lst) : PyObject() {
    data = *lst;
    
    dict["__getitem__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyTuple::__getitem__);
    dict["__len__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyTuple::__len__);
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyTuple::__iter__);
    dict["__hash__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyTuple::__hash__);
    dict["__eq__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyTuple::__eq__);
}

PyTuple::~PyTuple() {
}

PyType* PyTuple::getType() {
    return PyTypes[PyTupleType];
}

int PyTuple::size() {
    return data.size();
}

string PyTuple::toString() {
    ostringstream s;
    
    s << "(";
    
    for (int i=0;i<data.size();i++) {
        if (data[i]->getType()->typeId()==PyStrType) 
            s << "\'" << data[i]->toString() << "\'";
        else
            s << data[i]->toString();
        
        if (i < data.size()-1) 
            s << ", ";
        
    }
    
    s << ")";
    
    return s.str();
}

PyObject* PyTuple::__str__(vector<PyObject*>* args) {
    ostringstream s;
    
    s << "(";
    
    for (int i=0;i<data.size();i++) {
        if (data[i]->getType()->typeId()==PyStrType) 
            s << "\'" << data[i]->callMethod("__repr__", args) << "\'";
        else
            s << data[i]->callMethod("__repr__", args);
        
        if (i < data.size()-1) 
            s << ", ";
        
    }
    
    s << ")";
    
    return new PyStr(s.str());
}

PyObject* PyTuple::__repr__(vector<PyObject*>* args) {
    return __str__(args);
}

PyObject* PyTuple::getVal(int index) {
        if (index >= data.size()) {
        throw new PyException(PYSTOPITERATIONEXCEPTION,"Stop Iteration");
    }
    
    return data[index];
}

PyObject* PyTuple::__hash__(vector<PyObject*>* args) {
    ostringstream msg; 

    if (args->size() != 0) {
        msg << "TypeError expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str(),__FILE__,__LINE__);  
    }

    int k;
    unsigned int hash_val = 0;

    for (k=0; k < data.size(); k++) {
        PyObject* obj = data[k];

        PyInt* h = (PyInt*) obj->callMethod("__hash__", args);

        hash_val = hash_val + h->getVal();
    }

    hash_val = hash_val % 128;

    return new PyInt(hash_val);
}

PyObject* PyTuple::__eq__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 1) {
        msg << "TypeError expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str(),__FILE__,__LINE__);  
    }

    PyObject* obj = (*args)[0];

    if (obj->getType() != this->getType()) {
        return new PyBool(false);
    }

    PyTuple* other = (PyTuple*) (*args)[0];

    return new PyBool(data == other->data);
}

PyObject* PyTuple::__getitem__(vector<PyObject*>* args) {
    ostringstream msg; 

    if (args->size() != 1) {
        msg << "TypeError expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str(),__FILE__,__LINE__);  
    }
    
    PyInt* intObj = (PyInt*) (*args)[0];
    
    int index = intObj->getVal();
    
    if (index >= data.size()) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Index out of range.");
    }
    
    return data[index];
}

PyObject* PyTuple::__len__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str(),__FILE__,__LINE__);  
    }
    return new PyInt(data.size());
}

PyObject* PyTuple::__iter__(vector<PyObject*>* args) {
    ostringstream msg;
    
    if (args->size() != 0) {
        msg << "TypeError expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str(),__FILE__,__LINE__);  
    }
    
    return new PyTupleIterator(this);
}
